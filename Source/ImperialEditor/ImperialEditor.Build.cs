using UnrealBuildTool;

public class ImperialEditor : ModuleRules
{
	public ImperialEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "Public/ImperialEditor.h";
		bEnforceIWYU = true;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"UMG",
			"GameplayTags",
			"GameplayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"Slate",
			"SlateCore",
			"AssetRegistry",
			"UnrealEd",
			"EditorStyle",
			"RawMesh",
			"RHI",
			"RenderCore",
			"ImageCore",
			"ImageWrapper",
			"EngineSettings",
			"GraphEditor",
			"BlueprintGraph",
			"PropertyEditor",
			"ApplicationCore",
			"Json",
			"JsonUtilities",
			"Landscape",
			"Blutility",
			"UnrealEd",
			"DeveloperSettings",
			"PhysicsCore",
			"EditorWidgets",
			"WorkspaceMenuStructure",
			"Imperial"
		});
	}
}