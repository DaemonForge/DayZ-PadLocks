modded class ActionConstructor {
	
	void RegisterActions(TTypenameArray actions) {
		super.RegisterActions(actions);
		actions.Insert(ActionLockOpenFence);
		actions.Insert(ActionSetPadlockPin);
		actions.Insert(ActionOpenLockInterface);
		actions.Insert(ActionCutPadlock);
	}
};