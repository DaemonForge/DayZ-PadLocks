modded class MissionGameplay 
{
	protected bool m_PadlockRPCRegistered;
	
	override void OnMissionStart()
	{
		super.OnMissionStart();
		Print("[Padlock][Client] Requesting Config From Server");
		RegisterPadlockRPCClient();
		
		ScriptRPC rpc = new ScriptRPC();
		rpc.Send(null, PADLOCK_CONFIG_REQUEST, true, null);
	}
	
	protected void RegisterPadlockRPCClient()
	{
		if (m_PadlockRPCRegistered)
		{
			return;
		}
		GetDayZGame().Event_OnRPC.Insert(Padlock_OnRPC_Client);
		m_PadlockRPCRegistered = true;
	}
	
	void Padlock_OnRPC_Client(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{
		if (rpc_type == PADLOCK_CONFIG_RESPONSE && GetGame().IsClient())
		{
			PadlockConfig config = new PadlockConfig;
			if (!ctx.Read(config))
			{
				Print("[Padlock][Client] Failed to read config from server");
				return;
			}
			Print("[Padlock][Client] Received Config From Server");
			Class.CastTo(PadlockConfig.m_Config, config);
		}
	}
};