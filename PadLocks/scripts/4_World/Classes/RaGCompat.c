#ifdef RAG_CORE

// Block normal open when padlocked
modded class ActionOpenRaGItem
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		ItemBase ragitem = ItemBase.Cast(target.GetObject());
		if (ragitem && ragitem.IsPadlocked() && !ragitem.IsOpen())
		{
			return false;
		}
		return super.ActionCondition(player, target, item);
	}
}

// Add padlock actions to all RaG containers
modded class RaG_ContainerBase
{
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionPadlockOpenStorage);
		AddAction(ActionSetPadlockPin);
		AddAction(ActionOpenLockInterface);
	}
}

#endif

#ifdef RAG_BASEITEMS

// Block the baseitems-specific open/close when padlocked and closed
modded class ActionOpenCloseRaGBaseItem
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		ItemBase building = ItemBase.Cast(target.GetObject());
		if (building && building.IsPadlocked() && !building.IsOpen())
		{
			return false;
		}
		return super.ActionCondition(player, target, item);
	}
}

#endif
