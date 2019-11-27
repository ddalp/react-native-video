// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once
#include "ReactPackageProvider.g.h"

using namespace winrt::Microsoft::ReactNative::Bridge;

namespace winrt::ReactNativeVideoLibraryCPP::implementation {

struct ReactPackageProvider : ReactPackageProviderT<ReactPackageProvider> {
  ReactPackageProvider() = default;

  void CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept;
};

} // namespace winrt::SampleLibraryCPP::implementation

namespace winrt::ReactNativeVideoLibraryCPP::factory_implementation {

struct ReactPackageProvider : ReactPackageProviderT<ReactPackageProvider, implementation::ReactPackageProvider> {};

} // namespace winrt::SampleLibraryCPP::factory_implementation
