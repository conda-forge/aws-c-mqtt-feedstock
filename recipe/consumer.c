#include <aws/mqtt/mqtt.h>
#include <aws/common/byte_buf.h>
#include <stdio.h>
int main(void) {
    aws_mqtt_library_init(aws_default_allocator());
    struct aws_byte_cursor topic = aws_byte_cursor_from_c_str("sensors/arm64/temp");
    struct aws_byte_cursor wildcard = aws_byte_cursor_from_c_str("sensors/+/temp");
    struct aws_byte_cursor invalid = aws_byte_cursor_from_c_str("sensors/#/temp");
    if (!aws_mqtt_is_valid_topic(&topic) || aws_mqtt_is_valid_topic(&wildcard) ||
        !aws_mqtt_is_valid_topic_filter(&wildcard) || aws_mqtt_is_valid_topic_filter(&invalid)) return 1;
    const unsigned char malformed[] = {0xc0, 0xaf};
    struct aws_byte_cursor bad_utf8 = aws_byte_cursor_from_array(malformed, sizeof(malformed));
    if (aws_mqtt_validate_utf8_text(topic) || aws_mqtt_validate_utf8_text(bad_utf8) == AWS_OP_SUCCESS) return 2;
    aws_mqtt_library_clean_up();
    puts("MQTT topic, wildcard filter and malformed UTF-8 checks passed");
    return 0;
}
