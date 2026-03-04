modded class MissionServer
{
	protected bool m_PadlockRPCRegistered;
	
	override void OnInit()
	{
		super.OnInit();
		
		Print("[Padlock] OnInit");
		EnsurePadlockConfigLoaded();
		RegisterPadlockRPCServer();
	}
	
	protected void RegisterPadlockRPCServer()
	{
		if (m_PadlockRPCRegistered)
		{
			return;
		}
		GetDayZGame().Event_OnRPC.Insert(Padlock_OnRPC_Server);
		m_PadlockRPCRegistered = true;
	}
	
	void Padlock_OnRPC_Server(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		if (rpc_type == PADLOCK_CONFIG_REQUEST && GetGame().IsServer())
		{
			if (!sender)
			{
				return;
			}
			
			EnsurePadlockConfigLoaded();
			ScriptRPC rpc = new ScriptRPC();
			rpc.Write(PadlockConfig.m_Config);
			rpc.Send(null, PADLOCK_CONFIG_RESPONSE, true, sender);
		}
	}
	
	protected void EnsurePadlockConfigLoaded()
	{
		if (!GetGame().IsServer())
		{
			return;
		}
		if (!PadlockConfig.m_Config)
		{
			PadlockConfig.m_Config = new PadlockConfig;
			PadlockConfig.m_Config.Load();
		}
	}
}