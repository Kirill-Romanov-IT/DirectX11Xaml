﻿#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"
#include "Content\SampleFpsTextRenderer.h"

// Прорисовывает содержимое Direct2D и 3D на экране.
namespace DirectX11Xaml
{
	class DirectX11XamlMain : public DX::IDeviceNotify
	{
	public:
		DirectX11XamlMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~DirectX11XamlMain();
		void CreateWindowSizeDependentResources();
		void StartTracking() { m_sceneRenderer->StartTracking(); }
		void TrackingUpdate(float positionX) { m_pointerLocationX = positionX; }
		void StopTracking() { m_sceneRenderer->StopTracking(); }
		bool IsTracking() { return m_sceneRenderer->IsTracking(); }
		void StartRenderLoop();
		void StopRenderLoop();
		Concurrency::critical_section& GetCriticalSection() { return m_criticalSection; }

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();
		void ToggleCubeVisibility();
		bool IsCubeVisible() const;

	private:
		void ProcessInput();
		void Update();
		bool Render();

		// Кэшированный указатель на ресурсы устройства.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: замените это собственными визуализаторами содержимого.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;

		Windows::Foundation::IAsyncAction^ m_renderLoopWorker;
		Concurrency::critical_section m_criticalSection;

		// Таймер цикла прорисовки.
		DX::StepTimer m_timer;

		// Отслеживание текущего положения указателя ввода.
		float m_pointerLocationX;
		bool m_isCubeVisible;
	};
}