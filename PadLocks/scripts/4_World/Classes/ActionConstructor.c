modded class ActionConstructor {
	
	override void RegisterActions(TTypenameArray actions) {
		super.RegisterActions(actions);
		actions.Insert(ActionLockOpenFence);
		actions.Insert(ActionPadlockOpenStorage);
		actions.Insert(ActionSetPadlockPin);
		actions.Insert(ActionOpenLockInterface);
		actions.Insert(ActionCutPadlock);
	}
};  