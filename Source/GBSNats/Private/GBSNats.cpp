#include "GBSNats.h"

#include "Developer/Settings/Public/ISettingsModule.h"
#include "UObject/Package.h"


#define LOCTEXT_NAMESPACE "FGBSNatsModule"


void FGBSNatsModule::StartupModule()
{
}

void FGBSNatsModule::ShutdownModule()
{
}

IMPLEMENT_MODULE(FGBSNatsModule, GBSNats)
DEFINE_LOG_CATEGORY(LogGBSNats);

#undef LOCTEXT_NAMESPACE

