modded class MissionServer extends MissionBase
{
	override void OnInit() {
		super.OnInit();
		
		Print("[Padlock] OnInit");
		GetPadlockConfig();
		GetRPCManager().AddRPC( "Padlock", "RPCPadlockConfig", this, SingeplayerExecutionType.Both );
	} 
	
	void RPCPadlockConfig( CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target ) {
		PlayerIdentity RequestedBy = PlayerIdentity.Cast(sender);
		if (RequestedBy){
			GetRPCManager().SendRPC("Padlock", "RPCPadlockConfig", new Param1< PadlockConfig >( GetPadlockConfig() ), true, RequestedBy);
		}
	}
}


modded class MissionGameplay 
{
	override void OnMissionStart(){
		super.OnMissionStart();
		GetRPCManager().AddRPC( "Padlock", "RPCNotificationsConfig", this, SingeplayerExecutionType.Both );
		Print("[Padlock][Client] Requesting Config From Server");
		GetRPCManager().SendRPC("Padlock", "RPCPadlockConfig", new Param1< PadlockConfig >( NULL ), true, NULL);
	}
	
	
	void RPCPadlockConfig( CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target ) {
		Param1< PadlockConfig > data;
		if ( !ctx.Read( data ) ) return;
		Print("[Padlock][Client] Received Config From Server");
		Class.CastTo(PadlockConfig.m_Config, data.param1);
	}
};