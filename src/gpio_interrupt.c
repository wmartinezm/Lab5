#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

#define DEV_IN DT_NODELABEL(gpioa)
#define DEV_OUT DT_NODELABEL(gpioa)
#define PIN_OUT 0
#define PIN_IN 1

struct gpio_callback callback;
const struct device *dev_in, *dev_out;
//message queue items
struct message{};
K_MSGQ_DEFINE(request, sizeof(int), 32, 4);
//thread items
struct k_thread threads;
#define STACKSIZE 1000
K_THREAD_STACK_DEFINE(thread_stacks, STACKSIZE);

//interrupt handler
void pin_interrupt(const struct device *port,
                   struct gpio_callback *cb,
                   gpio_port_pins_t pins)
{

    //k_busy_wait(300);
    //k_busy_wait(300);
    //gpio_pin_toggle(dev_out, PIN_OUT);

    //add message to queue
    struct message data = {};
    k_msgq_put(&request, 1, K_FOREVER);  //put in data and how long it stays in the queue

}

//Thread reads messages from queue and toggles the output pin when a message is received.
//called by thread to perform work
void thread_work(struct k_msgq *work_input)
{
    while(1)
    {
        int i;
        k_msgq_get(work_input, i, K_FOREVER);
        k_busy_wait(300);
        gpio_pin_toggle(dev_out, PIN_OUT);
    }
}



void interrupt_main(void)
{



    k_thread_create(&threads,
                    thread_stacks,
                    STACKSIZE,
                    (k_thread_entry_t) thread_work,
                    &request,
                    NULL,
                    NULL,
                    K_PRIO_COOP(7),
                    0,
                    K_NO_WAIT);

    dev_in = device_get_binding(DT_LABEL(DEV_IN));
    dev_out = device_get_binding(DT_LABEL(DEV_OUT));

    gpio_pin_configure(dev_out, PIN_OUT, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure(dev_in, PIN_IN, GPIO_INPUT);
    gpio_pin_interrupt_configure(dev_in, PIN_IN, GPIO_INT_EDGE_RISING);
    gpio_init_callback(&callback, pin_interrupt, 1 << PIN_IN);
    gpio_add_callback(dev_in, &callback);

    k_sleep(K_FOREVER);

}