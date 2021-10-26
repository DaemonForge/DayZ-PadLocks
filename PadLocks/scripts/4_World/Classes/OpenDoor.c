class ActionLockOpenFence: ActionOpenFence
{
	bool IsLockedDoor = false;
	override string GetText() {
		if (IsLockedDoor){ return "Unlock Padlocked Door"; }
		return "Open Padlocked Door";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Fence fence;
		if ( (Class.CastTo(fence, target.GetObject()) || Class.CastTo(fence, target.GetParent())) && fence.CanUseConstruction() && fence.IsPadlocked() && !fence.IsOpened()) {
			if (!fence.CanUnlockPadlock(player.GetIdentity())){
				IsLockedDoor = true;
			} else {
				IsLockedDoor = false;
			}
			return true;
		}
		return false;
	}
		
	override void OnStartServer( ActionData action_data ) {
		Fence fence;
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		if ((Class.CastTo(fence, action_data.m_Target.GetObject()) || Class.CastTo(fence, action_data.m_Target.GetParent()))  && fence.IsPadlocked() && player && player.GetIdentity()){
			if ( fence.CanUnlockPadlock(player.GetIdentity())){
				fence.OpenFence();
			} else {
				fence.GetPadlock().RPCSingleParam(PADLOCK_OPENREQUEST, new Param1<bool>(true), true, player.GetIdentity());
			}
		}
	}
}

class ActionSetPadlockPin extends ActionInteractBase {
	
	void ActionSetPadlockPin()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}
	
	override string GetText() {
		return "Set Padlock Pin";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Fence fence;
		if ( (Class.CastTo(fence, target.GetObject()) || Class.CastTo(fence, target.GetParent())) ){
			if ( fence.CanUseConstruction() && fence.GetPadlock() && !fence.IsPadlocked() && !fence.IsOpened()) {
				return true;
			}
		}
		return false;
	}
		
	override void OnStartServer( ActionData action_data ) {
		Fence fence;
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		if ((Class.CastTo(fence, action_data.m_Target.GetObject()) || Class.CastTo(fence, action_data.m_Target.GetParent())) && fence.GetPadlock() && player && player.GetIdentity()){
			fence.GetPadlock().RPCSingleParam(PADLOCK_OPENREQUEST, new Param1<bool>(true), true, player.GetIdentity());
		}
	}

}


modded class ActionConstructor {
	
	void RegisterActions(TTypenameArray actions) {
		super.RegisterActions(actions);
		actions.Insert(ActionLockOpenFence);
		actions.Insert(ActionSetPadlockPin);
	}
};