// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ReactPackageProvider.h"
#if __has_include("ReactPackageProvider.g.cpp")
#include "ReactPackageProvider.g.cpp"
#endif

#include "ReactVideoViewManager.h"

using namespace winrt::Microsoft::ReactNative::Bridge;
using namespace winrt::Microsoft::ReactNative;

namespace winrt::ReactNativeVideoLibraryCPP::implementation {

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept {
  packageBuilder.AddViewManager(L"ReactVideoViewManager", [](IReactContext const& reactContext) {
	  return winrt::make<ReactVideoViewManager>(reactContext);
  });
}

} // namespace winrt::ReactNativeVideoLibraryCPP::implementation
