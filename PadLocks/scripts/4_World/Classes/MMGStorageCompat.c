#ifdef mmg_storage

// Block normal open/close when padlocked and closed
modded class ActionMMGCloseAndOpen
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		mmg_storage_openable_base crate = mmg_storage_openable_base.Cast(target.GetObject());
		if (crate && crate.IsPadlocked() && !crate.IsOpen())
		{
			return false;
		}
		return super.ActionCondition(player, target, item);
	}
}

// Add padlock actions and ensure the attachment slot is visible
modded class mmg_storage_openable_base
{
	override bool CanDisplayAttachmentCategory(string category_name)
	{
		if (category_name == "CodeLock")
			return true;
		return super.CanDisplayAttachmentCategory(category_name);
	}

	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionPadlockOpenStorage);
		AddAction(ActionSetPadlockPin);
		AddAction(ActionOpenLockInterface);
	}
}

#endif
