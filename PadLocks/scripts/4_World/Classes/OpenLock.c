class ActionOpenLockInterfaceCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(1);
	}
};


class ActionOpenLockInterface : ActionContinuousBase {
	
	void ActionOpenLockInterface() {
		m_CallbackClass = ActionOpenLockInterfaceCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_CRAFTING;
		m_FullBody = false;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTCursor;
		m_ConditionItem = new CCINone;
	}
	
	override string GetText()
	{
		return "Manage Lock";
	}
	
	override typename GetInputType()
	{
		return ContinuousInteractActionInput;
	}
	
	override bool HasTarget()
	{
		return true;
	}
	
	override bool HasProgress()
	{
		return true;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item ) {
		ItemBase fence;
		if ( (Class.CastTo(fence, target.GetObject()) || Class.CastTo(fence, target.GetParent())) ){
			if ( fence.GetPadlock() && fence.IsPadlocked() && !fence.IsOpen()) {
				return true;
			}
		}
		
		return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data ) {
		ItemBase fence;
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		if ((Class.CastTo(fence, action_data.m_Target.GetObject()) || Class.CastTo(fence, action_data.m_Target.GetParent())) && fence.GetPadlock() && player && player.GetIdentity()){
			fence.GetPadlock().RPCSingleParam(PADLOCK_OPENREQUEST, new Param1<bool>(true), true, player.GetIdentity());
		}
	}
}