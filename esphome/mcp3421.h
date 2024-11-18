#include "esphome.h"

class MCP3421Sensor : public PollingComponent, public Sensor {
public:
    MCP3421Sensor(esphome::i2c::ArduinoI2CBus *parent) : PollingComponent(1000), i2c_parent(parent) {}

    void setup() override {
        // No additional setup needed for MCP3421
    }

    void update() override {
        uint8_t data[3];
        
        // Read method without flags
        if (i2c_parent->read(0x68, data, 3) == i2c::ERROR_OK) {
            int16_t raw_value = (data[0] << 8) | data[1];
            float voltage = raw_value * 0.001;  // Adjust as needed for MCP3421
            publish_state(voltage);
        } else {
            ESP_LOGW("MCP3421", "Failed to read from MCP3421");
        }
    }

private:
    esphome::i2c::ArduinoI2CBus *i2c_parent;
};
