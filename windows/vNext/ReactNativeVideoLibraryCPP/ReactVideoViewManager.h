// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "winrt/Microsoft.ReactNative.Bridge.h"

using namespace winrt;
using namespace Microsoft::ReactNative::Bridge;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::Media::Core;

namespace winrt::ReactNativeVideoLibraryCPP::implementation {

	struct ReactVideoViewManager : winrt::implements<
		ReactVideoViewManager,
		IViewManager,
		IViewManagerWithNativeProperties,
		IViewManagerWithExportedViewConstants,
		IViewManagerWithExportedEventTypeConstants>
	{
	public:
		ReactVideoViewManager(winrt::Microsoft::ReactNative::Bridge::IReactContext const& reactContext);
		// IViewManager
		winrt::hstring Name() noexcept;
		
		winrt::Microsoft::ReactNative::Bridge::IReactContext ReactContext() noexcept;

		FrameworkElement CreateView() noexcept;

		//IViewManagerWithExportedViewConstants
		IMapView<winrt::hstring, IInspectable> ExportedViewConstants() noexcept;

		// IViewManagerWithNativeProperties
		IMapView<winrt::hstring, ViewManagerPropertyType>
			NativeProps() noexcept;

		void UpdateProperties(
			FrameworkElement const& view,
			IMapView<winrt::hstring, IInspectable> const
			& propertyMap);

		// IViewManagerWithExportedEventTypeConstants
		IMapView<winrt::hstring, winrt::Windows::Foundation::IInspectable>
			ExportedCustomBubblingEventTypeConstants() noexcept;

		IMapView<winrt::hstring, winrt::Windows::Foundation::IInspectable>
			ExportedCustomDirectEventTypeConstants() noexcept;
	
	private:
		winrt::Microsoft::ReactNative::Bridge::IReactContext m_reactContext{ nullptr };
	};

} // namespace winrt::ReactNativeVideoLibraryCPP::implementation
