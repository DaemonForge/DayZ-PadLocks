class ActionLockOpenFence: ActionOpenFence
{
	bool IsLockedDoor = false;
	override string GetText()
	{
		if (IsLockedDoor){ return "#locked"; }
		return "#open";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		if ( targetObject && targetObject.CanUseConstruction() )
		{
			Fence fence = Fence.Cast( targetObject );
			if (!fence.CanUnlockDoor(player)){
				IsLockedDoor = true;
			} else {
				IsLockedDoor = false;
			}
			return true;
		}
		return false;
	}
	
	override void OnStartServer( ActionData action_data ) {
		Fence fence = Fence.Cast( action_data.m_Target.GetObject() );
		if (fence && fence.CanUnlockDoor(action_data.m_Player)){
			fence.OpenFence();
		}
	}
}