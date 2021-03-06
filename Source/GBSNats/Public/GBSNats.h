#pragma once

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGBSNats, Log, All);

class UGBSNatsSettings;

class FGBSNatsModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline FGBSNatsModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FGBSNatsModule>("GBSNats");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("GBSNats");
	}

	/** Getter for internal settings object to support runtime configuration changes */
	// UGBSNatsSettings* GetSettings() const;

protected:
	/** Module settings */
	// UGBSNatsSettings* ModuleSettings;
};
