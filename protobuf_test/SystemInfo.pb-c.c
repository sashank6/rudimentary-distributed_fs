/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: SystemInfo.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "SystemInfo.pb-c.h"
void   system_info__init
                     (SystemInfo         *message)
{
  static SystemInfo init_value = SYSTEM_INFO__INIT;
  *message = init_value;
}
size_t system_info__get_packed_size
                     (const SystemInfo *message)
{
  assert(message->base.descriptor == &system_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t system_info__pack
                     (const SystemInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &system_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t system_info__pack_to_buffer
                     (const SystemInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &system_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
SystemInfo *
       system_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (SystemInfo *)
     protobuf_c_message_unpack (&system_info__descriptor,
                                allocator, len, data);
}
void   system_info__free_unpacked
                     (SystemInfo *message,
                      ProtobufCAllocator *allocator)
{
  assert(message->base.descriptor == &system_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor system_info__field_descriptors[2] =
{
  {
    "foldersize",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(SystemInfo, foldersize),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "port",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(SystemInfo, port),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned system_info__field_indices_by_name[] = {
  0,   /* field[0] = foldersize */
  1,   /* field[1] = port */
};
static const ProtobufCIntRange system_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor system_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "SystemInfo",
  "SystemInfo",
  "SystemInfo",
  "",
  sizeof(SystemInfo),
  2,
  system_info__field_descriptors,
  system_info__field_indices_by_name,
  1,  system_info__number_ranges,
  (ProtobufCMessageInit) system_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};