// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ReactVideoViewManager.h"
#include "ReactVideoView.h"

namespace winrt::ReactNativeVideoLibraryCPP::implementation {

	ReactVideoViewManager::ReactVideoViewManager(IReactContext const& reactContext)
		: m_reactContext{ reactContext } {}

	IReactContext ReactVideoViewManager::ReactContext() noexcept {
		return m_reactContext;
	}

	// IViewManager
	hstring ReactVideoViewManager::Name() noexcept {
		return L"RCTVideo";
	}

	FrameworkElement ReactVideoViewManager::CreateView() noexcept {
		auto reactVideoView = winrt::ReactNativeVideoLibraryCPP::ReactVideoView(m_reactContext);
		return reactVideoView;
	}

	IMapView<winrt::hstring, IInspectable> ReactVideoViewManager::ExportedViewConstants() noexcept {
		auto exportedConstants = winrt::single_threaded_map<hstring, IInspectable>();
		exportedConstants.Insert(L"ScaleNone", box_value(to_hstring(std::to_string((int)Stretch::None))));
		exportedConstants.Insert(L"ScaleToFill", box_value(to_hstring(std::to_string((int)Stretch::UniformToFill))));
		exportedConstants.Insert(L"ScaleAspectFit", box_value(to_hstring(std::to_string((int)Stretch::Uniform))));
		exportedConstants.Insert(L"ScaleAspectFill", box_value(to_hstring(std::to_string((int)Stretch::Fill))));
		return exportedConstants.GetView();
	}

	// IViewManagerWithExportedEventTypeConstants
	IMapView<hstring, IInspectable> ReactVideoViewManager::ExportedCustomBubblingEventTypeConstants() noexcept {
		auto constants = winrt::single_threaded_map<hstring, IInspectable>();
		return constants.GetView();
	}

	IMapView<hstring, IInspectable> ReactVideoViewManager::ExportedCustomDirectEventTypeConstants() noexcept {
		auto constants = winrt::single_threaded_map<hstring, IInspectable>();

		{
			auto registration = winrt::single_threaded_map<hstring, IInspectable>();
			registration.Insert(L"registrationName", box_value(L"onLoad"));
			constants.Insert(L"topLoad", registration.GetView());
		}
		{
			auto registration = winrt::single_threaded_map<hstring, IInspectable>();
			registration.Insert(L"registrationName", box_value(L"onEnd"));
			constants.Insert(L"topEnd", registration.GetView());
		}

		return constants.GetView();
	}


	// IViewManagerWithNativeProperties
	IMapView<hstring, ViewManagerPropertyType> ReactVideoViewManager::NativeProps() noexcept {
		auto nativeProps = winrt::single_threaded_map<hstring, ViewManagerPropertyType>();
		nativeProps.Insert(L"src", ViewManagerPropertyType::Map);
		nativeProps.Insert(L"resizeMode", ViewManagerPropertyType::String);
		nativeProps.Insert(L"repeat", ViewManagerPropertyType::Boolean);
		nativeProps.Insert(L"paused", ViewManagerPropertyType::Boolean);
		nativeProps.Insert(L"muted", ViewManagerPropertyType::Boolean);
		nativeProps.Insert(L"volume", ViewManagerPropertyType::Number);
		nativeProps.Insert(L"seek", ViewManagerPropertyType::Number);
		nativeProps.Insert(L"controls", ViewManagerPropertyType::Boolean);
		nativeProps.Insert(L"fullscreen", ViewManagerPropertyType::Boolean);
		nativeProps.Insert(L"progressUpdateInterval", ViewManagerPropertyType::Number);

		return nativeProps.GetView();
	}

	void ReactVideoViewManager::UpdateProperties(
		FrameworkElement const& view,
		IMapView<hstring, IInspectable> const& propertyMap) {
		if (auto reactVideoView = view.try_as<winrt::ReactNativeVideoLibraryCPP::ReactVideoView>()) {
			for (auto const& pair : propertyMap) {
				auto const& propertyName = pair.Key();
				auto const& propertyValue = pair.Value();
				if (propertyValue == nullptr) {
					continue;
				}
				if (propertyName == L"src") {
					auto srcView = propertyValue.try_as<IMapView<hstring, IInspectable>>();
					if (const auto & uriProperty = srcView.TryLookup(L"uri")) {
						reactVideoView.Set_UriString(winrt::unbox_value<hstring>(uriProperty));
					}
				}
				else if (propertyName == L"resizeMode") {
					reactVideoView.Stretch(static_cast<Stretch>(std::stoul(winrt::to_string(winrt::unbox_value<hstring>(propertyValue)))));
				}
				else if (propertyName == L"repeat") {
					reactVideoView.Set_IsLoopingEnabled(winrt::unbox_value<bool>(propertyValue));
				}
				else if (propertyName == L"paused")
				{
					reactVideoView.Set_Paused(winrt::unbox_value<bool>(propertyValue));
				}
				else if (propertyName == L"muted") {
					reactVideoView.Set_Muted(winrt::unbox_value<bool>(propertyValue));
				}
				else if (propertyName == L"volume") {
					reactVideoView.Set_Volume(winrt::unbox_value<double>(propertyValue));
				}
				else if (propertyName == L"seek") {
					reactVideoView.Set_Position(winrt::unbox_value<double>(propertyValue));
				}
				else if (propertyName == L"controls") {
					reactVideoView.Set_Controls(winrt::unbox_value<bool>(propertyValue));
				}
				else if (propertyName == L"fullscreen") {
					reactVideoView.Set_FullScreen(winrt::unbox_value<bool>(propertyValue));
				}
				else if (propertyName == L"progressUpdateInterval") {
					reactVideoView.Set_progressUpdateInterval(winrt::unbox_value<int64_t>(propertyValue));
				}
			}
		}
	}
} // namespace winrt::ReactNativeVideoLibraryCPP::implementation
