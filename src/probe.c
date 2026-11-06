/*
 * Power probe for breadboard testing (no multimeter needed).
 * Reads pin P0.31 once per second and logs whether it sees 3.3 V.
 * Touch a wire from P0.31 to the point you want to test.
 */
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(probe, LOG_LEVEL_INF);

#define PROBE_PIN 31

static const struct device *gpio0_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));

static void probe_fn(struct k_work *work);
static K_WORK_DELAYABLE_DEFINE(probe_work, probe_fn);

static void probe_fn(struct k_work *work) {
    int v = gpio_pin_get_raw(gpio0_dev, PROBE_PIN);
    LOG_INF("PROBE P0.31: %s", v > 0 ? "HIGH  -> 3.3 V present" : "LOW   -> no voltage");
    k_work_schedule(&probe_work, K_SECONDS(1));
}

static int probe_init(void) {
    if (!device_is_ready(gpio0_dev)) {
        LOG_ERR("PROBE: gpio0 not ready");
        return 0;
    }
    /* Pull-down: an unconnected probe wire reads LOW */
    gpio_pin_configure(gpio0_dev, PROBE_PIN, GPIO_INPUT | GPIO_PULL_DOWN);
    k_work_schedule(&probe_work, K_SECONDS(5));
    return 0;
}

SYS_INIT(probe_init, APPLICATION, 99);
