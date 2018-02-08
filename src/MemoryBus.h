#pragma once

#include "Base.h"
#include <algorithm>
#include <array>
#include <functional>

using MemoryRange = std::pair<uint16_t, uint16_t>;

struct IMemoryBusDevice {
    virtual uint8_t Read(uint16_t address) const = 0;
    virtual void Write(uint16_t address, uint8_t value) = 0;
};

class MemoryBus {
public:
    MemoryBus() { std::fill(m_deviceMap.begin(), m_deviceMap.end(), nullptr); }

    void ConnectDevice(IMemoryBusDevice& device, MemoryRange range) {
        for (uint32_t address = range.first; address <= range.second; ++address) {
            assert(m_deviceMap[address] == nullptr); // Should't map an address twice
            m_deviceMap[address] = &device;
        }
    }

    //@TODO: Move this callback stuff out of here, perhaps in some DebuggerMemoryBus class.
    using OnReadCallback = std::function<void(uint16_t, uint8_t)>;
    using OnWriteCallback = std::function<void(uint16_t, uint8_t)>;
    void RegisterCallbacks(OnReadCallback onReadCallback, OnWriteCallback onWriteCallback) {
        m_onReadCallback = onReadCallback;
        m_onWriteCallback = onWriteCallback;
    }

    void SetCallbacksEnabled(bool enabled) { m_callbacksEnabled = enabled; }

    uint8_t Read(uint16_t address) const {
        auto device = m_deviceMap[address];
        ASSERT_MSG(device, "Unmapped address");
        uint8_t value = device->Read(address);

        if (m_callbacksEnabled && m_onReadCallback)
            m_onReadCallback(address, value);

        return value;
    }

    void Write(uint16_t address, uint8_t value) {
        if (m_callbacksEnabled && m_onWriteCallback)
            m_onWriteCallback(address, value);

        auto device = m_deviceMap[address];
        ASSERT_MSG(device, "Unmapped address");
        device->Write(address, value);
    }

private:
    std::array<IMemoryBusDevice*, 65536> m_deviceMap;

    bool m_callbacksEnabled = true;
    OnReadCallback m_onReadCallback;
    OnWriteCallback m_onWriteCallback;
};
