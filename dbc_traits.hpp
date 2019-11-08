#pragma once

#include "dbc_structures.hpp"
#include "dbc_meta.hpp"

namespace datastores
{
    template <typename T> struct meta_type {
        using type = std::nullptr_t;
    };

    template <typename T> struct record_type {
        using type = std::nullptr_t;
    };
    template <> struct record_type<Startup_StringsMeta> {
        using type = Startup_StringsEntry;
    };

    template <> struct meta_type<Startup_StringsEntry> {
        using type = Startup_StringsMeta;
    };

    template <> struct record_type<ItemSparseMeta> {
        using type = ItemSparseEntry;
    };

    template <> struct meta_type<ItemSparseEntry> {
        using type = ItemSparseMeta;
    };

    template <> struct record_type<ItemMeta> {
        using type = ItemEntry;
    };

    template <> struct meta_type<ItemEntry> {
        using type = ItemMeta;
    };

    template <> struct record_type<SpellVisualKitMeta> {
        using type = SpellVisualKitEntry;
    };

    template <> struct meta_type<SpellVisualKitEntry> {
        using type = SpellVisualKitMeta;
    };

    template <> struct record_type<SpellVisualEffectNameMeta> {
        using type = SpellVisualEffectNameEntry;
    };

    template <> struct meta_type<SpellVisualEffectNameEntry> {
        using type = SpellVisualEffectNameMeta;
    };

    template <> struct record_type<SpellEffectMeta> {
        using type = SpellEffectEntry;
    };

    template <> struct meta_type<SpellEffectEntry> {
        using type = SpellEffectMeta;
    };

    template <> struct record_type<ParticleColorMeta> {
        using type = ParticleColorEntry;
    };

    template <> struct meta_type<ParticleColorEntry> {
        using type = ParticleColorMeta;
    };

    template <> struct record_type<ObjectEffectPackageElemMeta> {
        using type = ObjectEffectPackageElemEntry;
    };

    template <> struct meta_type<ObjectEffectPackageElemEntry> {
        using type = ObjectEffectPackageElemMeta;
    };

    template <> struct record_type<ObjectEffectPackageMeta> {
        using type = ObjectEffectPackageEntry;
    };

    template <> struct meta_type<ObjectEffectPackageEntry> {
        using type = ObjectEffectPackageMeta;
    };

    template <> struct record_type<ObjectEffectModifierMeta> {
        using type = ObjectEffectModifierEntry;
    };

    template <> struct meta_type<ObjectEffectModifierEntry> {
        using type = ObjectEffectModifierMeta;
    };

    template <> struct record_type<ObjectEffectGroupMeta> {
        using type = ObjectEffectGroupEntry;
    };

    template <> struct meta_type<ObjectEffectGroupEntry> {
        using type = ObjectEffectGroupMeta;
    };

    template <> struct record_type<ObjectEffectMeta> {
        using type = ObjectEffectEntry;
    };

    template <> struct meta_type<ObjectEffectEntry> {
        using type = ObjectEffectMeta;
    };

    template <> struct record_type<NameGenMeta> {
        using type = NameGenEntry;
    };

    template <> struct meta_type<NameGenEntry> {
        using type = NameGenMeta;
    };

    template <> struct record_type<LoadingScreensMeta> {
        using type = LoadingScreensEntry;
    };

    template <> struct meta_type<LoadingScreensEntry> {
        using type = LoadingScreensMeta;
    };

    template <> struct record_type<ItemVisualEffectsMeta> {
        using type = ItemVisualEffectsEntry;
    };

    template <> struct meta_type<ItemVisualEffectsEntry> {
        using type = ItemVisualEffectsMeta;
    };

    template <> struct record_type<ItemVisualsMeta> {
        using type = ItemVisualsEntry;
    };

    template <> struct meta_type<ItemVisualsEntry> {
        using type = ItemVisualsMeta;
    };

    template <> struct record_type<ItemDisplayInfoMeta> {
        using type = ItemDisplayInfoEntry;
    };

    template <> struct meta_type<ItemDisplayInfoEntry> {
        using type = ItemDisplayInfoMeta;
    };

    template <> struct record_type<HelmetGeosetVisDataMeta> {
        using type = HelmetGeosetVisDataEntry;
    };

    template <> struct meta_type<HelmetGeosetVisDataEntry> {
        using type = HelmetGeosetVisDataMeta;
    };

    template <> struct record_type<GuildColorEmblemMeta> {
        using type = GuildColorEmblemEntry;
    };

    template <> struct meta_type<GuildColorEmblemEntry> {
        using type = GuildColorEmblemMeta;
    };

    template <> struct record_type<GuildColorBorderMeta> {
        using type = GuildColorBorderEntry;
    };

    template <> struct meta_type<GuildColorBorderEntry> {
        using type = GuildColorBorderMeta;
    };

    template <> struct record_type<GuildColorBackgroundMeta> {
        using type = GuildColorBackgroundEntry;
    };

    template <> struct meta_type<GuildColorBackgroundEntry> {
        using type = GuildColorBackgroundMeta;
    };

    template <> struct record_type<GlueScreenEmoteMeta> {
        using type = GlueScreenEmoteEntry;
    };

    template <> struct meta_type<GlueScreenEmoteEntry> {
        using type = GlueScreenEmoteMeta;
    };

    template <> struct record_type<GameTipsMeta> {
        using type = GameTipsEntry;
    };

    template <> struct meta_type<GameTipsEntry> {
        using type = GameTipsMeta;
    };

    template <> struct record_type<CreatureModelDataMeta> {
        using type = CreatureModelDataEntry;
    };

    template <> struct meta_type<CreatureModelDataEntry> {
        using type = CreatureModelDataMeta;
    };

    template <> struct record_type<CreatureFamilyMeta> {
        using type = CreatureFamilyEntry;
    };

    template <> struct meta_type<CreatureFamilyEntry> {
        using type = CreatureFamilyMeta;
    };

    template <> struct record_type<CreatureDisplayInfoExtraMeta> {
        using type = CreatureDisplayInfoExtraEntry;
    };

    template <> struct meta_type<CreatureDisplayInfoExtraEntry> {
        using type = CreatureDisplayInfoExtraMeta;
    };

    template <> struct record_type<CreatureDisplayInfoMeta> {
        using type = CreatureDisplayInfoEntry;
    };

    template <> struct meta_type<CreatureDisplayInfoEntry> {
        using type = CreatureDisplayInfoMeta;
    };

    template <> struct record_type<CharStartOutfitMeta> {
        using type = CharStartOutfitEntry;
    };

    template <> struct meta_type<CharStartOutfitEntry> {
        using type = CharStartOutfitMeta;
    };

    template <> struct record_type<AnimReplacementSetMeta> {
        using type = AnimReplacementSetEntry;
    };

    template <> struct meta_type<AnimReplacementSetEntry> {
        using type = AnimReplacementSetMeta;
    };

    template <> struct record_type<AnimReplacementMeta> {
        using type = AnimReplacementEntry;
    };

    template <> struct meta_type<AnimReplacementEntry> {
        using type = AnimReplacementMeta;
    };

    template <> struct record_type<AnimKitSegmentMeta> {
        using type = AnimKitSegmentEntry;
    };

    template <> struct meta_type<AnimKitSegmentEntry> {
        using type = AnimKitSegmentMeta;
    };

    template <> struct record_type<AnimKitPriorityMeta> {
        using type = AnimKitPriorityEntry;
    };

    template <> struct meta_type<AnimKitPriorityEntry> {
        using type = AnimKitPriorityMeta;
    };

    template <> struct record_type<SoundProviderPreferencesMeta> {
        using type = SoundProviderPreferencesEntry;
    };

    template <> struct meta_type<SoundProviderPreferencesEntry> {
        using type = SoundProviderPreferencesMeta;
    };

    template <> struct record_type<SpamMessagesMeta> {
        using type = SpamMessagesEntry;
    };

    template <> struct meta_type<SpamMessagesEntry> {
        using type = SpamMessagesMeta;
    };

    template <> struct record_type<SoundFilterElemMeta> {
        using type = SoundFilterElemEntry;
    };

    template <> struct meta_type<SoundFilterElemEntry> {
        using type = SoundFilterElemMeta;
    };

    template <> struct record_type<SoundFilterMeta> {
        using type = SoundFilterEntry;
    };

    template <> struct meta_type<SoundFilterEntry> {
        using type = SoundFilterMeta;
    };

    template <> struct record_type<ResistancesMeta> {
        using type = ResistancesEntry;
    };

    template <> struct meta_type<ResistancesEntry> {
        using type = ResistancesMeta;
    };

    template <> struct record_type<NamesReservedMeta> {
        using type = NamesReservedEntry;
    };

    template <> struct meta_type<NamesReservedEntry> {
        using type = NamesReservedMeta;
    };

    template <> struct record_type<NamesProfanityMeta> {
        using type = NamesProfanityEntry;
    };

    template <> struct meta_type<NamesProfanityEntry> {
        using type = NamesProfanityMeta;
    };

    template <> struct record_type<MovieVariationMeta> {
        using type = MovieVariationEntry;
    };

    template <> struct meta_type<MovieVariationEntry> {
        using type = MovieVariationMeta;
    };

    template <> struct record_type<MovieFileDataMeta> {
        using type = MovieFileDataEntry;
    };

    template <> struct meta_type<MovieFileDataEntry> {
        using type = MovieFileDataMeta;
    };

    template <> struct record_type<MovieMeta> {
        using type = MovieEntry;
    };

    template <> struct meta_type<MovieEntry> {
        using type = MovieMeta;
    };

    template <> struct record_type<ItemSubClassMeta> {
        using type = ItemSubClassEntry;
    };

    template <> struct meta_type<ItemSubClassEntry> {
        using type = ItemSubClassMeta;
    };

    template <> struct record_type<ItemClassMeta> {
        using type = ItemClassEntry;
    };

    template <> struct meta_type<ItemClassEntry> {
        using type = ItemClassMeta;
    };

    template <> struct record_type<FileDataMeta> {
        using type = FileDataEntry;
    };

    template <> struct meta_type<FileDataEntry> {
        using type = FileDataMeta;
    };

    template <> struct record_type<FactionTemplateMeta> {
        using type = FactionTemplateEntry;
    };

    template <> struct meta_type<FactionTemplateEntry> {
        using type = FactionTemplateMeta;
    };

    template <> struct record_type<FactionGroupMeta> {
        using type = FactionGroupEntry;
    };

    template <> struct meta_type<FactionGroupEntry> {
        using type = FactionGroupMeta;
    };

    template <> struct record_type<ChrRacesMeta> {
        using type = ChrRacesEntry;
    };

    template <> struct meta_type<ChrRacesEntry> {
        using type = ChrRacesMeta;
    };

    template <> struct record_type<ChrClassesMeta> {
        using type = ChrClassesEntry;
    };

    template <> struct meta_type<ChrClassesEntry> {
        using type = ChrClassesMeta;
    };

    template <> struct record_type<ChatProfanityMeta> {
        using type = ChatProfanityEntry;
    };

    template <> struct meta_type<ChatProfanityEntry> {
        using type = ChatProfanityMeta;
    };

    template <> struct record_type<CharacterFacialHairStylesMeta> {
        using type = CharacterFacialHairStylesEntry;
    };

    template <> struct meta_type<CharacterFacialHairStylesEntry> {
        using type = CharacterFacialHairStylesMeta;
    };

    template <> struct record_type<CharSectionsMeta> {
        using type = CharSectionsEntry;
    };

    template <> struct meta_type<CharSectionsEntry> {
        using type = CharSectionsMeta;
    };

    template <> struct record_type<CharHairGeosetsMeta> {
        using type = CharHairGeosetsEntry;
    };

    template <> struct meta_type<CharHairGeosetsEntry> {
        using type = CharHairGeosetsMeta;
    };

    template <> struct record_type<CharBaseInfoMeta> {
        using type = CharBaseInfoEntry;
    };

    template <> struct meta_type<CharBaseInfoEntry> {
        using type = CharBaseInfoMeta;
    };

    template <> struct record_type<Cfg_ConfigsMeta> {
        using type = Cfg_ConfigsEntry;
    };

    template <> struct meta_type<Cfg_ConfigsEntry> {
        using type = Cfg_ConfigsMeta;
    };

    template <> struct record_type<Cfg_CategoriesMeta> {
        using type = Cfg_CategoriesEntry;
    };

    template <> struct meta_type<Cfg_CategoriesEntry> {
        using type = Cfg_CategoriesMeta;
    };

    template <> struct record_type<BannedAddOnsMeta> {
        using type = BannedAddOnsEntry;
    };

    template <> struct meta_type<BannedAddOnsEntry> {
        using type = BannedAddOnsMeta;
    };

    template <> struct record_type<AnimKitConfigBoneSetMeta> {
        using type = AnimKitConfigBoneSetEntry;
    };

    template <> struct meta_type<AnimKitConfigBoneSetEntry> {
        using type = AnimKitConfigBoneSetMeta;
    };

    template <> struct record_type<AnimKitConfigMeta> {
        using type = AnimKitConfigEntry;
    };

    template <> struct meta_type<AnimKitConfigEntry> {
        using type = AnimKitConfigMeta;
    };

    template <> struct record_type<AnimKitMeta> {
        using type = AnimKitEntry;
    };

    template <> struct meta_type<AnimKitEntry> {
        using type = AnimKitMeta;
    };

    template <> struct record_type<AnimKitBoneSetMeta> {
        using type = AnimKitBoneSetEntry;
    };

    template <> struct meta_type<AnimKitBoneSetEntry> {
        using type = AnimKitBoneSetMeta;
    };

    template <> struct record_type<AnimKitBoneSetAliasMeta> {
        using type = AnimKitBoneSetAliasEntry;
    };

    template <> struct meta_type<AnimKitBoneSetAliasEntry> {
        using type = AnimKitBoneSetAliasMeta;
    };

    template <> struct record_type<PhaseShiftZoneSoundsMeta> {
        using type = PhaseShiftZoneSoundsEntry;
    };

    template <> struct meta_type<PhaseShiftZoneSoundsEntry> {
        using type = PhaseShiftZoneSoundsMeta;
    };

    template <> struct record_type<WorldChunkSoundsMeta> {
        using type = WorldChunkSoundsEntry;
    };

    template <> struct meta_type<WorldChunkSoundsEntry> {
        using type = WorldChunkSoundsMeta;
    };

    template <> struct record_type<WorldStateZoneSoundsMeta> {
        using type = WorldStateZoneSoundsEntry;
    };

    template <> struct meta_type<WorldStateZoneSoundsEntry> {
        using type = WorldStateZoneSoundsMeta;
    };

    template <> struct record_type<ZoneMusicMeta> {
        using type = ZoneMusicEntry;
    };

    template <> struct meta_type<ZoneMusicEntry> {
        using type = ZoneMusicMeta;
    };

    template <> struct record_type<ZoneIntroMusicTableMeta> {
        using type = ZoneIntroMusicTableEntry;
    };

    template <> struct meta_type<ZoneIntroMusicTableEntry> {
        using type = ZoneIntroMusicTableMeta;
    };

    template <> struct record_type<WorldStateUIMeta> {
        using type = WorldStateUIEntry;
    };

    template <> struct meta_type<WorldStateUIEntry> {
        using type = WorldStateUIMeta;
    };

    template <> struct record_type<WorldSafeLocsMeta> {
        using type = WorldSafeLocsEntry;
    };

    template <> struct meta_type<WorldSafeLocsEntry> {
        using type = WorldSafeLocsMeta;
    };

    template <> struct record_type<WorldMapTransformsMeta> {
        using type = WorldMapTransformsEntry;
    };

    template <> struct meta_type<WorldMapTransformsEntry> {
        using type = WorldMapTransformsMeta;
    };

    template <> struct record_type<WorldMapOverlayMeta> {
        using type = WorldMapOverlayEntry;
    };

    template <> struct meta_type<WorldMapOverlayEntry> {
        using type = WorldMapOverlayMeta;
    };

    template <> struct record_type<WorldMapContinentMeta> {
        using type = WorldMapContinentEntry;
    };

    template <> struct meta_type<WorldMapContinentEntry> {
        using type = WorldMapContinentMeta;
    };

    template <> struct record_type<WorldMapAreaMeta> {
        using type = WorldMapAreaEntry;
    };

    template <> struct meta_type<WorldMapAreaEntry> {
        using type = WorldMapAreaMeta;
    };

    template <> struct record_type<WeaponSwingSounds2Meta> {
        using type = WeaponSwingSounds2Entry;
    };

    template <> struct meta_type<WeaponSwingSounds2Entry> {
        using type = WeaponSwingSounds2Meta;
    };

    template <> struct record_type<WeaponImpactSoundsMeta> {
        using type = WeaponImpactSoundsEntry;
    };

    template <> struct meta_type<WeaponImpactSoundsEntry> {
        using type = WeaponImpactSoundsMeta;
    };

    template <> struct record_type<World_PVP_AreaMeta> {
        using type = World_PVP_AreaEntry;
    };

    template <> struct meta_type<World_PVP_AreaEntry> {
        using type = World_PVP_AreaMeta;
    };

    template <> struct record_type<VocalUISoundsMeta> {
        using type = VocalUISoundsEntry;
    };

    template <> struct meta_type<VocalUISoundsEntry> {
        using type = VocalUISoundsMeta;
    };

    template <> struct record_type<VehicleUIIndSeatMeta> {
        using type = VehicleUIIndSeatEntry;
    };

    template <> struct meta_type<VehicleUIIndSeatEntry> {
        using type = VehicleUIIndSeatMeta;
    };

    template <> struct record_type<VehicleUIIndicatorMeta> {
        using type = VehicleUIIndicatorEntry;
    };

    template <> struct meta_type<VehicleUIIndicatorEntry> {
        using type = VehicleUIIndicatorMeta;
    };

    template <> struct record_type<VehicleSeatMeta> {
        using type = VehicleSeatEntry;
    };

    template <> struct meta_type<VehicleSeatEntry> {
        using type = VehicleSeatMeta;
    };

    template <> struct record_type<VehicleMeta> {
        using type = VehicleEntry;
    };

    template <> struct meta_type<VehicleEntry> {
        using type = VehicleMeta;
    };

    template <> struct record_type<UnitPowerBarMeta> {
        using type = UnitPowerBarEntry;
    };

    template <> struct meta_type<UnitPowerBarEntry> {
        using type = UnitPowerBarMeta;
    };

    template <> struct record_type<UnitBloodMeta> {
        using type = UnitBloodEntry;
    };

    template <> struct meta_type<UnitBloodEntry> {
        using type = UnitBloodMeta;
    };

    template <> struct record_type<UnitBloodLevelsMeta> {
        using type = UnitBloodLevelsEntry;
    };

    template <> struct meta_type<UnitBloodLevelsEntry> {
        using type = UnitBloodLevelsMeta;
    };

    template <> struct record_type<TransportRotationMeta> {
        using type = TransportRotationEntry;
    };

    template <> struct meta_type<TransportRotationEntry> {
        using type = TransportRotationMeta;
    };

    template <> struct record_type<TransportPhysicsMeta> {
        using type = TransportPhysicsEntry;
    };

    template <> struct meta_type<TransportPhysicsEntry> {
        using type = TransportPhysicsMeta;
    };

    template <> struct record_type<TransportAnimationMeta> {
        using type = TransportAnimationEntry;
    };

    template <> struct meta_type<TransportAnimationEntry> {
        using type = TransportAnimationMeta;
    };

    template <> struct record_type<TotemCategoryMeta> {
        using type = TotemCategoryEntry;
    };

    template <> struct meta_type<TotemCategoryEntry> {
        using type = TotemCategoryMeta;
    };

    template <> struct record_type<TerrainTypeSoundsMeta> {
        using type = TerrainTypeSoundsEntry;
    };

    template <> struct meta_type<TerrainTypeSoundsEntry> {
        using type = TerrainTypeSoundsMeta;
    };

    template <> struct record_type<TaxiPathMeta> {
        using type = TaxiPathEntry;
    };

    template <> struct meta_type<TaxiPathEntry> {
        using type = TaxiPathMeta;
    };

    template <> struct record_type<TaxiPathNodeMeta> {
        using type = TaxiPathNodeEntry;
    };

    template <> struct meta_type<TaxiPathNodeEntry> {
        using type = TaxiPathNodeMeta;
    };

    template <> struct record_type<TaxiNodesMeta> {
        using type = TaxiNodesEntry;
    };

    template <> struct meta_type<TaxiNodesEntry> {
        using type = TaxiNodesMeta;
    };

    template <> struct record_type<TalentTreePrimarySpellsMeta> {
        using type = TalentTreePrimarySpellsEntry;
    };

    template <> struct meta_type<TalentTreePrimarySpellsEntry> {
        using type = TalentTreePrimarySpellsMeta;
    };

    template <> struct record_type<TalentTabMeta> {
        using type = TalentTabEntry;
    };

    template <> struct meta_type<TalentTabEntry> {
        using type = TalentTabMeta;
    };

    template <> struct record_type<TalentMeta> {
        using type = TalentEntry;
    };

    template <> struct meta_type<TalentEntry> {
        using type = TalentMeta;
    };

    template <> struct record_type<SummonPropertiesMeta> {
        using type = SummonPropertiesEntry;
    };

    template <> struct meta_type<SummonPropertiesEntry> {
        using type = SummonPropertiesMeta;
    };

    template <> struct record_type<StringLookupsMeta> {
        using type = StringLookupsEntry;
    };

    template <> struct meta_type<StringLookupsEntry> {
        using type = StringLookupsMeta;
    };

    template <> struct record_type<StationeryMeta> {
        using type = StationeryEntry;
    };

    template <> struct meta_type<StationeryEntry> {
        using type = StationeryMeta;
    };

    template <> struct record_type<SpellVisualKitModelAttachMeta> {
        using type = SpellVisualKitModelAttachEntry;
    };

    template <> struct meta_type<SpellVisualKitModelAttachEntry> {
        using type = SpellVisualKitModelAttachMeta;
    };

    template <> struct record_type<SpellVisualKitAreaModelMeta> {
        using type = SpellVisualKitAreaModelEntry;
    };

    template <> struct meta_type<SpellVisualKitAreaModelEntry> {
        using type = SpellVisualKitAreaModelMeta;
    };

    template <> struct record_type<SpellVisualMeta> {
        using type = SpellVisualEntry;
    };

    template <> struct meta_type<SpellVisualEntry> {
        using type = SpellVisualMeta;
    };

    template <> struct record_type<SpellTotemsMeta> {
        using type = SpellTotemsEntry;
    };

    template <> struct meta_type<SpellTotemsEntry> {
        using type = SpellTotemsMeta;
    };

    template <> struct record_type<SpellTargetRestrictionsMeta> {
        using type = SpellTargetRestrictionsEntry;
    };

    template <> struct meta_type<SpellTargetRestrictionsEntry> {
        using type = SpellTargetRestrictionsMeta;
    };

    template <> struct record_type<SpellSpecialUnitEffectMeta> {
        using type = SpellSpecialUnitEffectEntry;
    };

    template <> struct meta_type<SpellSpecialUnitEffectEntry> {
        using type = SpellSpecialUnitEffectMeta;
    };

    template <> struct record_type<SpellShapeshiftFormMeta> {
        using type = SpellShapeshiftFormEntry;
    };

    template <> struct meta_type<SpellShapeshiftFormEntry> {
        using type = SpellShapeshiftFormMeta;
    };

    template <> struct record_type<SpellShapeshiftMeta> {
        using type = SpellShapeshiftEntry;
    };

    template <> struct meta_type<SpellShapeshiftEntry> {
        using type = SpellShapeshiftMeta;
    };

    template <> struct record_type<SpellScalingMeta> {
        using type = SpellScalingEntry;
    };

    template <> struct meta_type<SpellScalingEntry> {
        using type = SpellScalingMeta;
    };

    template <> struct record_type<SpellRuneCostMeta> {
        using type = SpellRuneCostEntry;
    };

    template <> struct meta_type<SpellRuneCostEntry> {
        using type = SpellRuneCostMeta;
    };

    template <> struct record_type<SpellReagentsMeta> {
        using type = SpellReagentsEntry;
    };

    template <> struct meta_type<SpellReagentsEntry> {
        using type = SpellReagentsMeta;
    };

    template <> struct record_type<SpellPowerMeta> {
        using type = SpellPowerEntry;
    };

    template <> struct meta_type<SpellPowerEntry> {
        using type = SpellPowerMeta;
    };

    template <> struct record_type<SpellRangeMeta> {
        using type = SpellRangeEntry;
    };

    template <> struct meta_type<SpellRangeEntry> {
        using type = SpellRangeMeta;
    };

    template <> struct record_type<SpellRadiusMeta> {
        using type = SpellRadiusEntry;
    };

    template <> struct meta_type<SpellRadiusEntry> {
        using type = SpellRadiusMeta;
    };

    template <> struct record_type<SpellMissileMotionMeta> {
        using type = SpellMissileMotionEntry;
    };

    template <> struct meta_type<SpellMissileMotionEntry> {
        using type = SpellMissileMotionMeta;
    };

    template <> struct record_type<SpellMissileMeta> {
        using type = SpellMissileEntry;
    };

    template <> struct meta_type<SpellMissileEntry> {
        using type = SpellMissileMeta;
    };

    template <> struct record_type<SpellMechanicMeta> {
        using type = SpellMechanicEntry;
    };

    template <> struct meta_type<SpellMechanicEntry> {
        using type = SpellMechanicMeta;
    };

    template <> struct record_type<SpellLevelsMeta> {
        using type = SpellLevelsEntry;
    };

    template <> struct meta_type<SpellLevelsEntry> {
        using type = SpellLevelsMeta;
    };

    template <> struct record_type<SpellItemEnchantmentConditionMeta> {
        using type = SpellItemEnchantmentConditionEntry;
    };

    template <> struct meta_type<SpellItemEnchantmentConditionEntry> {
        using type = SpellItemEnchantmentConditionMeta;
    };

    template <> struct record_type<SpellItemEnchantmentMeta> {
        using type = SpellItemEnchantmentEntry;
    };

    template <> struct meta_type<SpellItemEnchantmentEntry> {
        using type = SpellItemEnchantmentMeta;
    };

    template <> struct record_type<SpellInterruptsMeta> {
        using type = SpellInterruptsEntry;
    };

    template <> struct meta_type<SpellInterruptsEntry> {
        using type = SpellInterruptsMeta;
    };

    template <> struct record_type<SpellIconMeta> {
        using type = SpellIconEntry;
    };

    template <> struct meta_type<SpellIconEntry> {
        using type = SpellIconMeta;
    };

    template <> struct record_type<SpellFocusObjectMeta> {
        using type = SpellFocusObjectEntry;
    };

    template <> struct meta_type<SpellFocusObjectEntry> {
        using type = SpellFocusObjectMeta;
    };

    template <> struct record_type<SpellFlyoutItemMeta> {
        using type = SpellFlyoutItemEntry;
    };

    template <> struct meta_type<SpellFlyoutItemEntry> {
        using type = SpellFlyoutItemMeta;
    };

    template <> struct record_type<SpellFlyoutMeta> {
        using type = SpellFlyoutEntry;
    };

    template <> struct meta_type<SpellFlyoutEntry> {
        using type = SpellFlyoutMeta;
    };

    template <> struct record_type<SpellEquippedItemsMeta> {
        using type = SpellEquippedItemsEntry;
    };

    template <> struct meta_type<SpellEquippedItemsEntry> {
        using type = SpellEquippedItemsMeta;
    };

    template <> struct record_type<SpellEffectCameraShakesMeta> {
        using type = SpellEffectCameraShakesEntry;
    };

    template <> struct meta_type<SpellEffectCameraShakesEntry> {
        using type = SpellEffectCameraShakesMeta;
    };

    template <> struct record_type<SpellDurationMeta> {
        using type = SpellDurationEntry;
    };

    template <> struct meta_type<SpellDurationEntry> {
        using type = SpellDurationMeta;
    };

    template <> struct record_type<SpellDispelTypeMeta> {
        using type = SpellDispelTypeEntry;
    };

    template <> struct meta_type<SpellDispelTypeEntry> {
        using type = SpellDispelTypeMeta;
    };

    template <> struct record_type<SpellDifficultyMeta> {
        using type = SpellDifficultyEntry;
    };

    template <> struct meta_type<SpellDifficultyEntry> {
        using type = SpellDifficultyMeta;
    };

    template <> struct record_type<SpellDescriptionVariablesMeta> {
        using type = SpellDescriptionVariablesEntry;
    };

    template <> struct meta_type<SpellDescriptionVariablesEntry> {
        using type = SpellDescriptionVariablesMeta;
    };

    template <> struct record_type<SpellMeta> {
        using type = SpellEntry;
    };

    template <> struct meta_type<SpellEntry> {
        using type = SpellMeta;
    };

    template <> struct record_type<SpellCooldownsMeta> {
        using type = SpellCooldownsEntry;
    };

    template <> struct meta_type<SpellCooldownsEntry> {
        using type = SpellCooldownsMeta;
    };

    template <> struct record_type<SpellClassOptionsMeta> {
        using type = SpellClassOptionsEntry;
    };

    template <> struct meta_type<SpellClassOptionsEntry> {
        using type = SpellClassOptionsMeta;
    };

    template <> struct record_type<SpellChainEffectsMeta> {
        using type = SpellChainEffectsEntry;
    };

    template <> struct meta_type<SpellChainEffectsEntry> {
        using type = SpellChainEffectsMeta;
    };

    template <> struct record_type<SpellCategoryMeta> {
        using type = SpellCategoryEntry;
    };

    template <> struct meta_type<SpellCategoryEntry> {
        using type = SpellCategoryMeta;
    };

    template <> struct record_type<SpellCategoriesMeta> {
        using type = SpellCategoriesEntry;
    };

    template <> struct meta_type<SpellCategoriesEntry> {
        using type = SpellCategoriesMeta;
    };

    template <> struct record_type<SpellCastTimesMeta> {
        using type = SpellCastTimesEntry;
    };

    template <> struct meta_type<SpellCastTimesEntry> {
        using type = SpellCastTimesMeta;
    };

    template <> struct record_type<SpellCastingRequirementsMeta> {
        using type = SpellCastingRequirementsEntry;
    };

    template <> struct meta_type<SpellCastingRequirementsEntry> {
        using type = SpellCastingRequirementsMeta;
    };

    template <> struct record_type<SpellAuraVisXTalentTabMeta> {
        using type = SpellAuraVisXTalentTabEntry;
    };

    template <> struct meta_type<SpellAuraVisXTalentTabEntry> {
        using type = SpellAuraVisXTalentTabMeta;
    };

    template <> struct record_type<SpellAuraVisibilityMeta> {
        using type = SpellAuraVisibilityEntry;
    };

    template <> struct meta_type<SpellAuraVisibilityEntry> {
        using type = SpellAuraVisibilityMeta;
    };

    template <> struct record_type<SpellAuraRestrictionsMeta> {
        using type = SpellAuraRestrictionsEntry;
    };

    template <> struct meta_type<SpellAuraRestrictionsEntry> {
        using type = SpellAuraRestrictionsMeta;
    };

    template <> struct record_type<SpellAuraOptionsMeta> {
        using type = SpellAuraOptionsEntry;
    };

    template <> struct meta_type<SpellAuraOptionsEntry> {
        using type = SpellAuraOptionsMeta;
    };

    template <> struct record_type<SpellActivationOverlayMeta> {
        using type = SpellActivationOverlayEntry;
    };

    template <> struct meta_type<SpellActivationOverlayEntry> {
        using type = SpellActivationOverlayMeta;
    };

    template <> struct record_type<SoundAmbienceFlavorMeta> {
        using type = SoundAmbienceFlavorEntry;
    };

    template <> struct meta_type<SoundAmbienceFlavorEntry> {
        using type = SoundAmbienceFlavorMeta;
    };

    template <> struct record_type<SoundAmbienceMeta> {
        using type = SoundAmbienceEntry;
    };

    template <> struct meta_type<SoundAmbienceEntry> {
        using type = SoundAmbienceMeta;
    };

    template <> struct record_type<SkillTiersMeta> {
        using type = SkillTiersEntry;
    };

    template <> struct meta_type<SkillTiersEntry> {
        using type = SkillTiersMeta;
    };

    template <> struct record_type<SkillRaceClassInfoMeta> {
        using type = SkillRaceClassInfoEntry;
    };

    template <> struct meta_type<SkillRaceClassInfoEntry> {
        using type = SkillRaceClassInfoMeta;
    };

    template <> struct record_type<SkillLineMeta> {
        using type = SkillLineEntry;
    };

    template <> struct meta_type<SkillLineEntry> {
        using type = SkillLineMeta;
    };

    template <> struct record_type<SkillLineCategoryMeta> {
        using type = SkillLineCategoryEntry;
    };

    template <> struct meta_type<SkillLineCategoryEntry> {
        using type = SkillLineCategoryMeta;
    };

    template <> struct record_type<SkillLineAbilitySortedSpellMeta> {
        using type = SkillLineAbilitySortedSpellEntry;
    };

    template <> struct meta_type<SkillLineAbilitySortedSpellEntry> {
        using type = SkillLineAbilitySortedSpellMeta;
    };

    template <> struct record_type<SkillLineAbilityMeta> {
        using type = SkillLineAbilityEntry;
    };

    template <> struct meta_type<SkillLineAbilityEntry> {
        using type = SkillLineAbilityMeta;
    };

    template <> struct record_type<ServerMessagesMeta> {
        using type = ServerMessagesEntry;
    };

    template <> struct meta_type<ServerMessagesEntry> {
        using type = ServerMessagesMeta;
    };

    template <> struct record_type<ScreenLocationMeta> {
        using type = ScreenLocationEntry;
    };

    template <> struct meta_type<ScreenLocationEntry> {
        using type = ScreenLocationMeta;
    };

    template <> struct record_type<ScreenEffectMeta> {
        using type = ScreenEffectEntry;
    };

    template <> struct meta_type<ScreenEffectEntry> {
        using type = ScreenEffectMeta;
    };

    template <> struct record_type<ScalingStatValuesMeta> {
        using type = ScalingStatValuesEntry;
    };

    template <> struct meta_type<ScalingStatValuesEntry> {
        using type = ScalingStatValuesMeta;
    };

    template <> struct record_type<ScalingStatDistributionMeta> {
        using type = ScalingStatDistributionEntry;
    };

    template <> struct meta_type<ScalingStatDistributionEntry> {
        using type = ScalingStatDistributionMeta;
    };

    template <> struct record_type<RandPropPointsMeta> {
        using type = RandPropPointsEntry;
    };

    template <> struct meta_type<RandPropPointsEntry> {
        using type = RandPropPointsMeta;
    };

    template <> struct record_type<ResearchSiteMeta> {
        using type = ResearchSiteEntry;
    };

    template <> struct meta_type<ResearchSiteEntry> {
        using type = ResearchSiteMeta;
    };

    template <> struct record_type<ResearchProjectMeta> {
        using type = ResearchProjectEntry;
    };

    template <> struct meta_type<ResearchProjectEntry> {
        using type = ResearchProjectMeta;
    };

    template <> struct record_type<ResearchFieldMeta> {
        using type = ResearchFieldEntry;
    };

    template <> struct meta_type<ResearchFieldEntry> {
        using type = ResearchFieldMeta;
    };

    template <> struct record_type<ResearchBranchMeta> {
        using type = ResearchBranchEntry;
    };

    template <> struct meta_type<ResearchBranchEntry> {
        using type = ResearchBranchMeta;
    };

    template <> struct record_type<QuestXPMeta> {
        using type = QuestXPEntry;
    };

    template <> struct meta_type<QuestXPEntry> {
        using type = QuestXPMeta;
    };

    template <> struct record_type<QuestSortMeta> {
        using type = QuestSortEntry;
    };

    template <> struct meta_type<QuestSortEntry> {
        using type = QuestSortMeta;
    };

    template <> struct record_type<QuestPOIPointMeta> {
        using type = QuestPOIPointEntry;
    };

    template <> struct meta_type<QuestPOIPointEntry> {
        using type = QuestPOIPointMeta;
    };

    template <> struct record_type<QuestPOIBlobMeta> {
        using type = QuestPOIBlobEntry;
    };

    template <> struct meta_type<QuestPOIBlobEntry> {
        using type = QuestPOIBlobMeta;
    };

    template <> struct record_type<QuestInfoMeta> {
        using type = QuestInfoEntry;
    };

    template <> struct meta_type<QuestInfoEntry> {
        using type = QuestInfoMeta;
    };

    template <> struct record_type<QuestFactionRewardMeta> {
        using type = QuestFactionRewardEntry;
    };

    template <> struct meta_type<QuestFactionRewardEntry> {
        using type = QuestFactionRewardMeta;
    };

    template <> struct record_type<PvpDifficultyMeta> {
        using type = PvpDifficultyEntry;
    };

    template <> struct meta_type<PvpDifficultyEntry> {
        using type = PvpDifficultyMeta;
    };

    template <> struct record_type<PowerDisplayMeta> {
        using type = PowerDisplayEntry;
    };

    template <> struct meta_type<PowerDisplayEntry> {
        using type = PowerDisplayMeta;
    };

    template <> struct record_type<PlayerConditionMeta> {
        using type = PlayerConditionEntry;
    };

    template <> struct meta_type<PlayerConditionEntry> {
        using type = PlayerConditionMeta;
    };

    template <> struct record_type<PhaseXPhaseGroupMeta> {
        using type = PhaseXPhaseGroupEntry;
    };

    template <> struct meta_type<PhaseXPhaseGroupEntry> {
        using type = PhaseXPhaseGroupMeta;
    };

    template <> struct record_type<PhaseMeta> {
        using type = PhaseEntry;
    };

    template <> struct meta_type<PhaseEntry> {
        using type = PhaseMeta;
    };

    template <> struct record_type<PaperDollItemFrameMeta> {
        using type = PaperDollItemFrameEntry;
    };

    template <> struct meta_type<PaperDollItemFrameEntry> {
        using type = PaperDollItemFrameMeta;
    };

    template <> struct record_type<PageTextMaterialMeta> {
        using type = PageTextMaterialEntry;
    };

    template <> struct meta_type<PageTextMaterialEntry> {
        using type = PageTextMaterialMeta;
    };

    template <> struct record_type<PackageMeta> {
        using type = PackageEntry;
    };

    template <> struct meta_type<PackageEntry> {
        using type = PackageMeta;
    };

    template <> struct record_type<OverrideSpellDataMeta> {
        using type = OverrideSpellDataEntry;
    };

    template <> struct meta_type<OverrideSpellDataEntry> {
        using type = OverrideSpellDataMeta;
    };

    template <> struct record_type<NumTalentsAtLevelMeta> {
        using type = NumTalentsAtLevelEntry;
    };

    template <> struct meta_type<NumTalentsAtLevelEntry> {
        using type = NumTalentsAtLevelMeta;
    };

    template <> struct record_type<NPCSoundsMeta> {
        using type = NPCSoundsEntry;
    };

    template <> struct meta_type<NPCSoundsEntry> {
        using type = NPCSoundsMeta;
    };

    template <> struct record_type<MountTypeMeta> {
        using type = MountTypeEntry;
    };

    template <> struct meta_type<MountTypeEntry> {
        using type = MountTypeMeta;
    };

    template <> struct record_type<MountCapabilityMeta> {
        using type = MountCapabilityEntry;
    };

    template <> struct meta_type<MountCapabilityEntry> {
        using type = MountCapabilityMeta;
    };

    template <> struct record_type<MaterialMeta> {
        using type = MaterialEntry;
    };

    template <> struct meta_type<MaterialEntry> {
        using type = MaterialMeta;
    };

    template <> struct record_type<MapDifficultyMeta> {
        using type = MapDifficultyEntry;
    };

    template <> struct meta_type<MapDifficultyEntry> {
        using type = MapDifficultyMeta;
    };

    template <> struct record_type<MailTemplateMeta> {
        using type = MailTemplateEntry;
    };

    template <> struct meta_type<MailTemplateEntry> {
        using type = MailTemplateMeta;
    };

    template <> struct record_type<LockTypeMeta> {
        using type = LockTypeEntry;
    };

    template <> struct meta_type<LockTypeEntry> {
        using type = LockTypeMeta;
    };

    template <> struct record_type<LockMeta> {
        using type = LockEntry;
    };

    template <> struct meta_type<LockEntry> {
        using type = LockMeta;
    };

    template <> struct record_type<LoadingScreenTaxiSplinesMeta> {
        using type = LoadingScreenTaxiSplinesEntry;
    };

    template <> struct meta_type<LoadingScreenTaxiSplinesEntry> {
        using type = LoadingScreenTaxiSplinesMeta;
    };

    template <> struct record_type<LfgDungeonsMeta> {
        using type = LfgDungeonsEntry;
    };

    template <> struct meta_type<LfgDungeonsEntry> {
        using type = LfgDungeonsMeta;
    };

    template <> struct record_type<LfgDungeonsGroupingMapMeta> {
        using type = LfgDungeonsGroupingMapEntry;
    };

    template <> struct meta_type<LfgDungeonsGroupingMapEntry> {
        using type = LfgDungeonsGroupingMapMeta;
    };

    template <> struct record_type<LfgDungeonGroupMeta> {
        using type = LfgDungeonGroupEntry;
    };

    template <> struct meta_type<LfgDungeonGroupEntry> {
        using type = LfgDungeonGroupMeta;
    };

    template <> struct record_type<LfgDungeonExpansionMeta> {
        using type = LfgDungeonExpansionEntry;
    };

    template <> struct meta_type<LfgDungeonExpansionEntry> {
        using type = LfgDungeonExpansionMeta;
    };

    template <> struct record_type<LanguagesMeta> {
        using type = LanguagesEntry;
    };

    template <> struct meta_type<LanguagesEntry> {
        using type = LanguagesMeta;
    };

    template <> struct record_type<LanguageWordsMeta> {
        using type = LanguageWordsEntry;
    };

    template <> struct meta_type<LanguageWordsEntry> {
        using type = LanguageWordsMeta;
    };

    template <> struct record_type<JournalInstanceMeta> {
        using type = JournalInstanceEntry;
    };

    template <> struct meta_type<JournalInstanceEntry> {
        using type = JournalInstanceMeta;
    };

    template <> struct record_type<JournalEncounterSectionMeta> {
        using type = JournalEncounterSectionEntry;
    };

    template <> struct meta_type<JournalEncounterSectionEntry> {
        using type = JournalEncounterSectionMeta;
    };

    template <> struct record_type<JournalEncounterMeta> {
        using type = JournalEncounterEntry;
    };

    template <> struct meta_type<JournalEncounterEntry> {
        using type = JournalEncounterMeta;
    };

    template <> struct record_type<JournalEncounterItemMeta> {
        using type = JournalEncounterItemEntry;
    };

    template <> struct meta_type<JournalEncounterItemEntry> {
        using type = JournalEncounterItemMeta;
    };

    template <> struct record_type<JournalEncounterCreatureMeta> {
        using type = JournalEncounterCreatureEntry;
    };

    template <> struct meta_type<JournalEncounterCreatureEntry> {
        using type = JournalEncounterCreatureMeta;
    };

    template <> struct record_type<ItemSubClassMaskMeta> {
        using type = ItemSubClassMaskEntry;
    };

    template <> struct meta_type<ItemSubClassMaskEntry> {
        using type = ItemSubClassMaskMeta;
    };

    template <> struct record_type<ItemSetMeta> {
        using type = ItemSetEntry;
    };

    template <> struct meta_type<ItemSetEntry> {
        using type = ItemSetMeta;
    };

    template <> struct record_type<ItemReforgeMeta> {
        using type = ItemReforgeEntry;
    };

    template <> struct meta_type<ItemReforgeEntry> {
        using type = ItemReforgeMeta;
    };

    template <> struct record_type<ItemRandomSuffixMeta> {
        using type = ItemRandomSuffixEntry;
    };

    template <> struct meta_type<ItemRandomSuffixEntry> {
        using type = ItemRandomSuffixMeta;
    };

    template <> struct record_type<ItemRandomPropertiesMeta> {
        using type = ItemRandomPropertiesEntry;
    };

    template <> struct meta_type<ItemRandomPropertiesEntry> {
        using type = ItemRandomPropertiesMeta;
    };

    template <> struct record_type<ItemPurchaseGroupMeta> {
        using type = ItemPurchaseGroupEntry;
    };

    template <> struct meta_type<ItemPurchaseGroupEntry> {
        using type = ItemPurchaseGroupMeta;
    };

    template <> struct record_type<ItemPriceBaseMeta> {
        using type = ItemPriceBaseEntry;
    };

    template <> struct meta_type<ItemPriceBaseEntry> {
        using type = ItemPriceBaseMeta;
    };

    template <> struct record_type<ItemPetFoodMeta> {
        using type = ItemPetFoodEntry;
    };

    template <> struct meta_type<ItemPetFoodEntry> {
        using type = ItemPetFoodMeta;
    };

    template <> struct record_type<ItemNameDescriptionMeta> {
        using type = ItemNameDescriptionEntry;
    };

    template <> struct meta_type<ItemNameDescriptionEntry> {
        using type = ItemNameDescriptionMeta;
    };

    template <> struct record_type<ItemLimitCategoryMeta> {
        using type = ItemLimitCategoryEntry;
    };

    template <> struct meta_type<ItemLimitCategoryEntry> {
        using type = ItemLimitCategoryMeta;
    };

    template <> struct record_type<ItemGroupSoundsMeta> {
        using type = ItemGroupSoundsEntry;
    };

    template <> struct meta_type<ItemGroupSoundsEntry> {
        using type = ItemGroupSoundsMeta;
    };

    template <> struct record_type<ItemDisenchantLootMeta> {
        using type = ItemDisenchantLootEntry;
    };

    template <> struct meta_type<ItemDisenchantLootEntry> {
        using type = ItemDisenchantLootMeta;
    };

    template <> struct record_type<ItemDamageWandMeta> {
        using type = ItemDamageWandEntry;
    };

    template <> struct meta_type<ItemDamageWandEntry> {
        using type = ItemDamageWandMeta;
    };

    template <> struct record_type<ItemDamageTwoHandCasterMeta> {
        using type = ItemDamageTwoHandCasterEntry;
    };

    template <> struct meta_type<ItemDamageTwoHandCasterEntry> {
        using type = ItemDamageTwoHandCasterMeta;
    };

    template <> struct record_type<ItemDamageTwoHandMeta> {
        using type = ItemDamageTwoHandEntry;
    };

    template <> struct meta_type<ItemDamageTwoHandEntry> {
        using type = ItemDamageTwoHandMeta;
    };

    template <> struct record_type<ItemDamageThrownMeta> {
        using type = ItemDamageThrownEntry;
    };

    template <> struct meta_type<ItemDamageThrownEntry> {
        using type = ItemDamageThrownMeta;
    };

    template <> struct record_type<ItemDamageRangedMeta> {
        using type = ItemDamageRangedEntry;
    };

    template <> struct meta_type<ItemDamageRangedEntry> {
        using type = ItemDamageRangedMeta;
    };

    template <> struct record_type<ItemDamageOneHandCasterMeta> {
        using type = ItemDamageOneHandCasterEntry;
    };

    template <> struct meta_type<ItemDamageOneHandCasterEntry> {
        using type = ItemDamageOneHandCasterMeta;
    };

    template <> struct record_type<ItemDamageOneHandMeta> {
        using type = ItemDamageOneHandEntry;
    };

    template <> struct meta_type<ItemDamageOneHandEntry> {
        using type = ItemDamageOneHandMeta;
    };

    template <> struct record_type<ItemDamageAmmoMeta> {
        using type = ItemDamageAmmoEntry;
    };

    template <> struct meta_type<ItemDamageAmmoEntry> {
        using type = ItemDamageAmmoMeta;
    };

    template <> struct record_type<ItemBagFamilyMeta> {
        using type = ItemBagFamilyEntry;
    };

    template <> struct meta_type<ItemBagFamilyEntry> {
        using type = ItemBagFamilyMeta;
    };

    template <> struct record_type<ItemArmorShieldMeta> {
        using type = ItemArmorShieldEntry;
    };

    template <> struct meta_type<ItemArmorShieldEntry> {
        using type = ItemArmorShieldMeta;
    };

    template <> struct record_type<ItemArmorTotalMeta> {
        using type = ItemArmorTotalEntry;
    };

    template <> struct meta_type<ItemArmorTotalEntry> {
        using type = ItemArmorTotalMeta;
    };

    template <> struct record_type<ItemArmorQualityMeta> {
        using type = ItemArmorQualityEntry;
    };

    template <> struct meta_type<ItemArmorQualityEntry> {
        using type = ItemArmorQualityMeta;
    };

    template <> struct record_type<ImportPriceWeaponMeta> {
        using type = ImportPriceWeaponEntry;
    };

    template <> struct meta_type<ImportPriceWeaponEntry> {
        using type = ImportPriceWeaponMeta;
    };

    template <> struct record_type<ImportPriceShieldMeta> {
        using type = ImportPriceShieldEntry;
    };

    template <> struct meta_type<ImportPriceShieldEntry> {
        using type = ImportPriceShieldMeta;
    };

    template <> struct record_type<ImportPriceQualityMeta> {
        using type = ImportPriceQualityEntry;
    };

    template <> struct meta_type<ImportPriceQualityEntry> {
        using type = ImportPriceQualityMeta;
    };

    template <> struct record_type<ImportPriceArmorMeta> {
        using type = ImportPriceArmorEntry;
    };

    template <> struct meta_type<ImportPriceArmorEntry> {
        using type = ImportPriceArmorMeta;
    };

    template <> struct record_type<HolidaysMeta> {
        using type = HolidaysEntry;
    };

    template <> struct meta_type<HolidaysEntry> {
        using type = HolidaysMeta;
    };

    template <> struct record_type<HolidayNamesMeta> {
        using type = HolidayNamesEntry;
    };

    template <> struct meta_type<HolidayNamesEntry> {
        using type = HolidayNamesMeta;
    };

    template <> struct record_type<HolidayDescriptionsMeta> {
        using type = HolidayDescriptionsEntry;
    };

    template <> struct meta_type<HolidayDescriptionsEntry> {
        using type = HolidayDescriptionsMeta;
    };

    template <> struct record_type<GuildPerkSpellsMeta> {
        using type = GuildPerkSpellsEntry;
    };

    template <> struct meta_type<GuildPerkSpellsEntry> {
        using type = GuildPerkSpellsMeta;
    };

    template <> struct record_type<gtSpellScalingMeta> {
        using type = gtSpellScalingEntry;
    };

    template <> struct meta_type<gtSpellScalingEntry> {
        using type = gtSpellScalingMeta;
    };

    template <> struct record_type<gtRegenMPPerSptMeta> {
        using type = gtRegenMPPerSptEntry;
    };

    template <> struct meta_type<gtRegenMPPerSptEntry> {
        using type = gtRegenMPPerSptMeta;
    };

    template <> struct record_type<gtOCTRegenMPMeta> {
        using type = gtOCTRegenMPEntry;
    };

    template <> struct meta_type<gtOCTRegenMPEntry> {
        using type = gtOCTRegenMPMeta;
    };

    template <> struct record_type<gtOCTHpPerStaminaMeta> {
        using type = gtOCTHpPerStaminaEntry;
    };

    template <> struct meta_type<gtOCTHpPerStaminaEntry> {
        using type = gtOCTHpPerStaminaMeta;
    };

    template <> struct record_type<gtOCTClassCombatRatingScalarMeta> {
        using type = gtOCTClassCombatRatingScalarEntry;
    };

    template <> struct meta_type<gtOCTClassCombatRatingScalarEntry> {
        using type = gtOCTClassCombatRatingScalarMeta;
    };

    template <> struct record_type<gtOCTBaseMPByClassMeta> {
        using type = gtOCTBaseMPByClassEntry;
    };

    template <> struct meta_type<gtOCTBaseMPByClassEntry> {
        using type = gtOCTBaseMPByClassMeta;
    };

    template <> struct record_type<gtOCTBaseHPByClassMeta> {
        using type = gtOCTBaseHPByClassEntry;
    };

    template <> struct meta_type<gtOCTBaseHPByClassEntry> {
        using type = gtOCTBaseHPByClassMeta;
    };

    template <> struct record_type<gtNPCManaCostScalerMeta> {
        using type = gtNPCManaCostScalerEntry;
    };

    template <> struct meta_type<gtNPCManaCostScalerEntry> {
        using type = gtNPCManaCostScalerMeta;
    };

    template <> struct record_type<gtChanceToSpellCritBaseMeta> {
        using type = gtChanceToSpellCritBaseEntry;
    };

    template <> struct meta_type<gtChanceToSpellCritBaseEntry> {
        using type = gtChanceToSpellCritBaseMeta;
    };

    template <> struct record_type<gtChanceToSpellCritMeta> {
        using type = gtChanceToSpellCritEntry;
    };

    template <> struct meta_type<gtChanceToSpellCritEntry> {
        using type = gtChanceToSpellCritMeta;
    };

    template <> struct record_type<gtChanceToMeleeCritBaseMeta> {
        using type = gtChanceToMeleeCritBaseEntry;
    };

    template <> struct meta_type<gtChanceToMeleeCritBaseEntry> {
        using type = gtChanceToMeleeCritBaseMeta;
    };

    template <> struct record_type<gtChanceToMeleeCritMeta> {
        using type = gtChanceToMeleeCritEntry;
    };

    template <> struct meta_type<gtChanceToMeleeCritEntry> {
        using type = gtChanceToMeleeCritMeta;
    };

    template <> struct record_type<gtCombatRatingsMeta> {
        using type = gtCombatRatingsEntry;
    };

    template <> struct meta_type<gtCombatRatingsEntry> {
        using type = gtCombatRatingsMeta;
    };

    template <> struct record_type<gtBarberShopCostBaseMeta> {
        using type = gtBarberShopCostBaseEntry;
    };

    template <> struct meta_type<gtBarberShopCostBaseEntry> {
        using type = gtBarberShopCostBaseMeta;
    };

    template <> struct record_type<GMTicketCategoryMeta> {
        using type = GMTicketCategoryEntry;
    };

    template <> struct meta_type<GMTicketCategoryEntry> {
        using type = GMTicketCategoryMeta;
    };

    template <> struct record_type<GMSurveySurveysMeta> {
        using type = GMSurveySurveysEntry;
    };

    template <> struct meta_type<GMSurveySurveysEntry> {
        using type = GMSurveySurveysMeta;
    };

    template <> struct record_type<GMSurveyQuestionsMeta> {
        using type = GMSurveyQuestionsEntry;
    };

    template <> struct meta_type<GMSurveyQuestionsEntry> {
        using type = GMSurveyQuestionsMeta;
    };

    template <> struct record_type<GMSurveyCurrentSurveyMeta> {
        using type = GMSurveyCurrentSurveyEntry;
    };

    template <> struct meta_type<GMSurveyCurrentSurveyEntry> {
        using type = GMSurveyCurrentSurveyMeta;
    };

    template <> struct record_type<GMSurveyAnswersMeta> {
        using type = GMSurveyAnswersEntry;
    };

    template <> struct meta_type<GMSurveyAnswersEntry> {
        using type = GMSurveyAnswersMeta;
    };

    template <> struct record_type<GlyphSlotMeta> {
        using type = GlyphSlotEntry;
    };

    template <> struct meta_type<GlyphSlotEntry> {
        using type = GlyphSlotMeta;
    };

    template <> struct record_type<GlyphPropertiesMeta> {
        using type = GlyphPropertiesEntry;
    };

    template <> struct meta_type<GlyphPropertiesEntry> {
        using type = GlyphPropertiesMeta;
    };

    template <> struct record_type<GemPropertiesMeta> {
        using type = GemPropertiesEntry;
    };

    template <> struct meta_type<GemPropertiesEntry> {
        using type = GemPropertiesMeta;
    };

    template <> struct record_type<GameTablesMeta> {
        using type = GameTablesEntry;
    };

    template <> struct meta_type<GameTablesEntry> {
        using type = GameTablesMeta;
    };

    template <> struct record_type<GameObjectDisplayInfoMeta> {
        using type = GameObjectDisplayInfoEntry;
    };

    template <> struct meta_type<GameObjectDisplayInfoEntry> {
        using type = GameObjectDisplayInfoMeta;
    };

    template <> struct record_type<GameObjectArtKitMeta> {
        using type = GameObjectArtKitEntry;
    };

    template <> struct meta_type<GameObjectArtKitEntry> {
        using type = GameObjectArtKitMeta;
    };

    template <> struct record_type<FootstepTerrainLookupMeta> {
        using type = FootstepTerrainLookupEntry;
    };

    template <> struct meta_type<FootstepTerrainLookupEntry> {
        using type = FootstepTerrainLookupMeta;
    };

    template <> struct record_type<FactionMeta> {
        using type = FactionEntry;
    };

    template <> struct meta_type<FactionEntry> {
        using type = FactionMeta;
    };

    template <> struct record_type<ExhaustionMeta> {
        using type = ExhaustionEntry;
    };

    template <> struct meta_type<ExhaustionEntry> {
        using type = ExhaustionMeta;
    };

    template <> struct record_type<EnvironmentalDamageMeta> {
        using type = EnvironmentalDamageEntry;
    };

    template <> struct meta_type<EnvironmentalDamageEntry> {
        using type = EnvironmentalDamageMeta;
    };

    template <> struct record_type<EmotesTextMeta> {
        using type = EmotesTextEntry;
    };

    template <> struct meta_type<EmotesTextEntry> {
        using type = EmotesTextMeta;
    };

    template <> struct record_type<EmotesTextSoundMeta> {
        using type = EmotesTextSoundEntry;
    };

    template <> struct meta_type<EmotesTextSoundEntry> {
        using type = EmotesTextSoundMeta;
    };

    template <> struct record_type<EmotesTextDataMeta> {
        using type = EmotesTextDataEntry;
    };

    template <> struct meta_type<EmotesTextDataEntry> {
        using type = EmotesTextDataMeta;
    };

    template <> struct record_type<EmotesMeta> {
        using type = EmotesEntry;
    };

    template <> struct meta_type<EmotesEntry> {
        using type = EmotesMeta;
    };

    template <> struct record_type<DurabilityQualityMeta> {
        using type = DurabilityQualityEntry;
    };

    template <> struct meta_type<DurabilityQualityEntry> {
        using type = DurabilityQualityMeta;
    };

    template <> struct record_type<DurabilityCostsMeta> {
        using type = DurabilityCostsEntry;
    };

    template <> struct meta_type<DurabilityCostsEntry> {
        using type = DurabilityCostsMeta;
    };

    template <> struct record_type<DungeonMapChunkMeta> {
        using type = DungeonMapChunkEntry;
    };

    template <> struct meta_type<DungeonMapChunkEntry> {
        using type = DungeonMapChunkMeta;
    };

    template <> struct record_type<DungeonMapMeta> {
        using type = DungeonMapEntry;
    };

    template <> struct meta_type<DungeonMapEntry> {
        using type = DungeonMapMeta;
    };

    template <> struct record_type<DungeonEncounterMeta> {
        using type = DungeonEncounterEntry;
    };

    template <> struct meta_type<DungeonEncounterEntry> {
        using type = DungeonEncounterMeta;
    };

    template <> struct record_type<DestructibleModelDataMeta> {
        using type = DestructibleModelDataEntry;
    };

    template <> struct meta_type<DestructibleModelDataEntry> {
        using type = DestructibleModelDataMeta;
    };

    template <> struct record_type<DeathThudLookupsMeta> {
        using type = DeathThudLookupsEntry;
    };

    template <> struct meta_type<DeathThudLookupsEntry> {
        using type = DeathThudLookupsMeta;
    };

    template <> struct record_type<DanceMovesMeta> {
        using type = DanceMovesEntry;
    };

    template <> struct meta_type<DanceMovesEntry> {
        using type = DanceMovesMeta;
    };

    template <> struct record_type<CurrencyCategoryMeta> {
        using type = CurrencyCategoryEntry;
    };

    template <> struct meta_type<CurrencyCategoryEntry> {
        using type = CurrencyCategoryMeta;
    };

    template <> struct record_type<CurrencyTypesMeta> {
        using type = CurrencyTypesEntry;
    };

    template <> struct meta_type<CurrencyTypesEntry> {
        using type = CurrencyTypesMeta;
    };

    template <> struct record_type<CreatureTypeMeta> {
        using type = CreatureTypeEntry;
    };

    template <> struct meta_type<CreatureTypeEntry> {
        using type = CreatureTypeMeta;
    };

    template <> struct record_type<CreatureSpellDataMeta> {
        using type = CreatureSpellDataEntry;
    };

    template <> struct meta_type<CreatureSpellDataEntry> {
        using type = CreatureSpellDataMeta;
    };

    template <> struct record_type<CreatureSoundDataMeta> {
        using type = CreatureSoundDataEntry;
    };

    template <> struct meta_type<CreatureSoundDataEntry> {
        using type = CreatureSoundDataMeta;
    };

    template <> struct record_type<CreatureMovementInfoMeta> {
        using type = CreatureMovementInfoEntry;
    };

    template <> struct meta_type<CreatureMovementInfoEntry> {
        using type = CreatureMovementInfoMeta;
    };

    template <> struct record_type<CreatureImmunitiesMeta> {
        using type = CreatureImmunitiesEntry;
    };

    template <> struct meta_type<CreatureImmunitiesEntry> {
        using type = CreatureImmunitiesMeta;
    };

    template <> struct record_type<CinematicSequencesMeta> {
        using type = CinematicSequencesEntry;
    };

    template <> struct meta_type<CinematicSequencesEntry> {
        using type = CinematicSequencesMeta;
    };

    template <> struct record_type<CinematicCameraMeta> {
        using type = CinematicCameraEntry;
    };

    template <> struct meta_type<CinematicCameraEntry> {
        using type = CinematicCameraMeta;
    };

    template <> struct record_type<ChrClassesXPowerTypesMeta> {
        using type = ChrClassesXPowerTypesEntry;
    };

    template <> struct meta_type<ChrClassesXPowerTypesEntry> {
        using type = ChrClassesXPowerTypesMeta;
    };

    template <> struct record_type<ChatChannelsMeta> {
        using type = ChatChannelsEntry;
    };

    template <> struct meta_type<ChatChannelsEntry> {
        using type = ChatChannelsMeta;
    };

    template <> struct record_type<CharTitlesMeta> {
        using type = CharTitlesEntry;
    };

    template <> struct meta_type<CharTitlesEntry> {
        using type = CharTitlesMeta;
    };

    template <> struct record_type<CastableRaidBuffsMeta> {
        using type = CastableRaidBuffsEntry;
    };

    template <> struct meta_type<CastableRaidBuffsEntry> {
        using type = CastableRaidBuffsMeta;
    };

    template <> struct record_type<CameraShakesMeta> {
        using type = CameraShakesEntry;
    };

    template <> struct meta_type<CameraShakesEntry> {
        using type = CameraShakesMeta;
    };

    template <> struct record_type<CameraModeMeta> {
        using type = CameraModeEntry;
    };

    template <> struct meta_type<CameraModeEntry> {
        using type = CameraModeMeta;
    };

    template <> struct record_type<BattlemasterListMeta> {
        using type = BattlemasterListEntry;
    };

    template <> struct meta_type<BattlemasterListEntry> {
        using type = BattlemasterListMeta;
    };

    template <> struct record_type<BarberShopStyleMeta> {
        using type = BarberShopStyleEntry;
    };

    template <> struct meta_type<BarberShopStyleEntry> {
        using type = BarberShopStyleMeta;
    };

    template <> struct record_type<BankBagSlotPricesMeta> {
        using type = BankBagSlotPricesEntry;
    };

    template <> struct meta_type<BankBagSlotPricesEntry> {
        using type = BankBagSlotPricesMeta;
    };

    template <> struct record_type<AuctionHouseMeta> {
        using type = AuctionHouseEntry;
    };

    template <> struct meta_type<AuctionHouseEntry> {
        using type = AuctionHouseMeta;
    };

    template <> struct record_type<ArmorLocationMeta> {
        using type = ArmorLocationEntry;
    };

    template <> struct meta_type<ArmorLocationEntry> {
        using type = ArmorLocationMeta;
    };

    template <> struct record_type<AreaTriggerMeta> {
        using type = AreaTriggerEntry;
    };

    template <> struct meta_type<AreaTriggerEntry> {
        using type = AreaTriggerMeta;
    };

    template <> struct record_type<AreaAssignmentMeta> {
        using type = AreaAssignmentEntry;
    };

    template <> struct meta_type<AreaAssignmentEntry> {
        using type = AreaAssignmentMeta;
    };

    template <> struct record_type<AreaPOISortedWorldStateMeta> {
        using type = AreaPOISortedWorldStateEntry;
    };

    template <> struct meta_type<AreaPOISortedWorldStateEntry> {
        using type = AreaPOISortedWorldStateMeta;
    };

    template <> struct record_type<AreaPOIMeta> {
        using type = AreaPOIEntry;
    };

    template <> struct meta_type<AreaPOIEntry> {
        using type = AreaPOIMeta;
    };

    template <> struct record_type<AreaGroupMeta> {
        using type = AreaGroupEntry;
    };

    template <> struct meta_type<AreaGroupEntry> {
        using type = AreaGroupMeta;
    };

    template <> struct record_type<Achievement_CategoryMeta> {
        using type = Achievement_CategoryEntry;
    };

    template <> struct meta_type<Achievement_CategoryEntry> {
        using type = Achievement_CategoryMeta;
    };

    template <> struct record_type<Achievement_CriteriaMeta> {
        using type = Achievement_CriteriaEntry;
    };

    template <> struct meta_type<Achievement_CriteriaEntry> {
        using type = Achievement_CriteriaMeta;
    };

    template <> struct record_type<AchievementMeta> {
        using type = AchievementEntry;
    };

    template <> struct meta_type<AchievementEntry> {
        using type = AchievementMeta;
    };

    template <> struct record_type<ItemCurrencyCostMeta> {
        using type = ItemCurrencyCostEntry;
    };

    template <> struct meta_type<ItemCurrencyCostEntry> {
        using type = ItemCurrencyCostMeta;
    };

    template <> struct record_type<ItemExtendedCostMeta> {
        using type = ItemExtendedCostEntry;
    };

    template <> struct meta_type<ItemExtendedCostEntry> {
        using type = ItemExtendedCostMeta;
    };

    template <> struct record_type<KeyChainMeta> {
        using type = KeyChainEntry;
    };

    template <> struct meta_type<KeyChainEntry> {
        using type = KeyChainMeta;
    };

    template <> struct record_type<DeclinedWordCasesMeta> {
        using type = DeclinedWordCasesEntry;
    };

    template <> struct meta_type<DeclinedWordCasesEntry> {
        using type = DeclinedWordCasesMeta;
    };

    template <> struct record_type<DeclinedWordMeta> {
        using type = DeclinedWordEntry;
    };

    template <> struct meta_type<DeclinedWordEntry> {
        using type = DeclinedWordMeta;
    };

    template <> struct record_type<ZoneLightPointMeta> {
        using type = ZoneLightPointEntry;
    };

    template <> struct meta_type<ZoneLightPointEntry> {
        using type = ZoneLightPointMeta;
    };

    template <> struct record_type<ZoneLightMeta> {
        using type = ZoneLightEntry;
    };

    template <> struct meta_type<ZoneLightEntry> {
        using type = ZoneLightMeta;
    };

    template <> struct record_type<WMOAreaTableMeta> {
        using type = WMOAreaTableEntry;
    };

    template <> struct meta_type<WMOAreaTableEntry> {
        using type = WMOAreaTableMeta;
    };

    template <> struct record_type<WeatherMeta> {
        using type = WeatherEntry;
    };

    template <> struct meta_type<WeatherEntry> {
        using type = WeatherMeta;
    };

    template <> struct record_type<TerrainTypeMeta> {
        using type = TerrainTypeEntry;
    };

    template <> struct meta_type<TerrainTypeEntry> {
        using type = TerrainTypeMeta;
    };

    template <> struct record_type<TerrainMaterialMeta> {
        using type = TerrainMaterialEntry;
    };

    template <> struct meta_type<TerrainMaterialEntry> {
        using type = TerrainMaterialMeta;
    };

    template <> struct record_type<SoundEntriesFallbacksMeta> {
        using type = SoundEntriesFallbacksEntry;
    };

    template <> struct meta_type<SoundEntriesFallbacksEntry> {
        using type = SoundEntriesFallbacksMeta;
    };

    template <> struct record_type<SoundEmittersMeta> {
        using type = SoundEmittersEntry;
    };

    template <> struct meta_type<SoundEmittersEntry> {
        using type = SoundEmittersMeta;
    };

    template <> struct record_type<SoundEmitterPillPointsMeta> {
        using type = SoundEmitterPillPointsEntry;
    };

    template <> struct meta_type<SoundEmitterPillPointsEntry> {
        using type = SoundEmitterPillPointsMeta;
    };

    template <> struct record_type<LiquidTypeMeta> {
        using type = LiquidTypeEntry;
    };

    template <> struct meta_type<LiquidTypeEntry> {
        using type = LiquidTypeMeta;
    };

    template <> struct record_type<LiquidObjectMeta> {
        using type = LiquidObjectEntry;
    };

    template <> struct meta_type<LiquidObjectEntry> {
        using type = LiquidObjectMeta;
    };

    template <> struct record_type<LiquidMaterialMeta> {
        using type = LiquidMaterialEntry;
    };

    template <> struct meta_type<LiquidMaterialEntry> {
        using type = LiquidMaterialMeta;
    };

    template <> struct record_type<LightSkyboxMeta> {
        using type = LightSkyboxEntry;
    };

    template <> struct meta_type<LightSkyboxEntry> {
        using type = LightSkyboxMeta;
    };

    template <> struct record_type<LightFloatBandMeta> {
        using type = LightFloatBandEntry;
    };

    template <> struct meta_type<LightFloatBandEntry> {
        using type = LightFloatBandMeta;
    };

    template <> struct record_type<LightMeta> {
        using type = LightEntry;
    };

    template <> struct meta_type<LightEntry> {
        using type = LightMeta;
    };

    template <> struct record_type<GroundEffectTextureMeta> {
        using type = GroundEffectTextureEntry;
    };

    template <> struct meta_type<GroundEffectTextureEntry> {
        using type = GroundEffectTextureMeta;
    };

    template <> struct record_type<GroundEffectDoodadMeta> {
        using type = GroundEffectDoodadEntry;
    };

    template <> struct meta_type<GroundEffectDoodadEntry> {
        using type = GroundEffectDoodadMeta;
    };

    template <> struct record_type<FootprintTexturesMeta> {
        using type = FootprintTexturesEntry;
    };

    template <> struct meta_type<FootprintTexturesEntry> {
        using type = FootprintTexturesMeta;
    };

    template <> struct record_type<MapMeta> {
        using type = MapEntry;
    };

    template <> struct meta_type<MapEntry> {
        using type = MapMeta;
    };

    template <> struct record_type<LightParamsMeta> {
        using type = LightParamsEntry;
    };

    template <> struct meta_type<LightParamsEntry> {
        using type = LightParamsMeta;
    };

    template <> struct record_type<LightIntBandMeta> {
        using type = LightIntBandEntry;
    };

    template <> struct meta_type<LightIntBandEntry> {
        using type = LightIntBandMeta;
    };

    template <> struct record_type<AreaTableMeta> {
        using type = AreaTableEntry;
    };

    template <> struct meta_type<AreaTableEntry> {
        using type = AreaTableMeta;
    };

    template <> struct record_type<AnimationDataMeta> {
        using type = AnimationDataEntry;
    };

    template <> struct meta_type<AnimationDataEntry> {
        using type = AnimationDataMeta;
    };

    template <> struct record_type<SoundEntriesMeta> {
        using type = SoundEntriesEntry;
    };

    template <> struct meta_type<SoundEntriesEntry> {
        using type = SoundEntriesMeta;
    };

    template <> struct record_type<SoundEntriesAdvancedMeta> {
        using type = SoundEntriesAdvancedEntry;
    };

    template <> struct meta_type<SoundEntriesAdvancedEntry> {
        using type = SoundEntriesAdvancedMeta;
    };

    template <> struct record_type<VideoHardwareMeta> {
        using type = VideoHardwareEntry;
    };

    template <> struct meta_type<VideoHardwareEntry> {
        using type = VideoHardwareMeta;
    };

}