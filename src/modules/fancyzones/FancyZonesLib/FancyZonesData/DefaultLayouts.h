#pragma once

#include <FancyZonesLib/FancyZonesData/Layout.h>
#include <FancyZonesLib/ModuleConstants.h>

#include <common/SettingsAPI/FileWatcher.h>
#include <common/SettingsAPI/settings_helpers.h>

namespace NonLocalizable
{
    namespace DefaultLayoutsIds
    {
        const static wchar_t* DefaultLayoutsArrayID = L"default-layouts";
        const static wchar_t* MonitorConfigurationTypeID = L"monitor-configuration";
        const static wchar_t* LayoutID = L"layout";
        const static wchar_t* UuidID = L"uuid";
        const static wchar_t* TypeID = L"type";
        const static wchar_t* ShowSpacingID = L"show-spacing";
        const static wchar_t* SpacingID = L"spacing";
        const static wchar_t* ZoneCountID = L"zone-count";
        const static wchar_t* SensitivityRadiusID = L"sensitivity-radius";
    }
}

enum class MonitorConfiguraionType
{
    Horizontal = 0,
    Vertical
};

class DefaultLayouts
{
public:
    using TDefaultLayoutsContainer = std::map<MonitorConfiguraionType, Layout>;

    static DefaultLayouts& instance();

    inline static std::wstring DefaultLayoutsFileName()
    {
        std::wstring saveFolderPath = PTSettingsHelper::get_module_save_folder_location(NonLocalizable::ModuleKey);
#if defined(UNIT_TESTS)
        return saveFolderPath + L"\\test-default-layouts.json";
#endif
        return saveFolderPath + L"\\default-layouts.json";
    }

    void LoadData();

    Layout GetDefaultLayout(MonitorConfiguraionType type = MonitorConfiguraionType::Horizontal) const noexcept;

private:
    DefaultLayouts();
    ~DefaultLayouts() = default;

    TDefaultLayoutsContainer m_layouts;
    std::unique_ptr<FileWatcher> m_fileWatcher;
};
