// Mattia De Prisco

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CrosshairHUD.generated.h"

/**
 * 
 */
UCLASS()
class CASTLEESCAPE_API ACrosshairHUD : public AHUD
{
    GENERATED_BODY()

protected:
    // This will be drawn at the center of the screen.
    UPROPERTY(EditDefaultsOnly)
    UTexture2D* CrosshairTexture;

public:
    // Primary draw call for the HUD.
    virtual void DrawHUD() override;
};
