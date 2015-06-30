// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: booth.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "booth.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace clientmsg {

namespace {

const ::google::protobuf::Descriptor* HoldBooth_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  HoldBooth_reflection_ = NULL;
const ::google::protobuf::Descriptor* BoothState_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  BoothState_reflection_ = NULL;
const ::google::protobuf::Descriptor* LeaveBooth_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  LeaveBooth_reflection_ = NULL;
const ::google::protobuf::Descriptor* GetBoothState_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  GetBoothState_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_booth_2eproto() {
  protobuf_AddDesc_booth_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "booth.proto");
  GOOGLE_CHECK(file != NULL);
  HoldBooth_descriptor_ = file->message_type(0);
  static const int HoldBooth_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HoldBooth, cityid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HoldBooth, boothid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HoldBooth, charid_),
  };
  HoldBooth_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      HoldBooth_descriptor_,
      HoldBooth::default_instance_,
      HoldBooth_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HoldBooth, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HoldBooth, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(HoldBooth));
  BoothState_descriptor_ = file->message_type(1);
  static const int BoothState_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BoothState, states_),
  };
  BoothState_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      BoothState_descriptor_,
      BoothState::default_instance_,
      BoothState_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BoothState, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BoothState, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(BoothState));
  LeaveBooth_descriptor_ = file->message_type(2);
  static const int LeaveBooth_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LeaveBooth, boothids_),
  };
  LeaveBooth_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      LeaveBooth_descriptor_,
      LeaveBooth::default_instance_,
      LeaveBooth_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LeaveBooth, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(LeaveBooth, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(LeaveBooth));
  GetBoothState_descriptor_ = file->message_type(3);
  static const int GetBoothState_offsets_[1] = {
  };
  GetBoothState_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      GetBoothState_descriptor_,
      GetBoothState::default_instance_,
      GetBoothState_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetBoothState, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GetBoothState, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(GetBoothState));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_booth_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    HoldBooth_descriptor_, &HoldBooth::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    BoothState_descriptor_, &BoothState::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    LeaveBooth_descriptor_, &LeaveBooth::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    GetBoothState_descriptor_, &GetBoothState::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_booth_2eproto() {
  delete HoldBooth::default_instance_;
  delete HoldBooth_reflection_;
  delete BoothState::default_instance_;
  delete BoothState_reflection_;
  delete LeaveBooth::default_instance_;
  delete LeaveBooth_reflection_;
  delete GetBoothState::default_instance_;
  delete GetBoothState_reflection_;
}

void protobuf_AddDesc_booth_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::protobuf_AddDesc_common_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013booth.proto\022\tclientmsg\032\014common.proto\"<"
    "\n\tHoldBooth\022\016\n\006cityid\030\001 \001(\r\022\017\n\007boothid\030\002"
    " \001(\r\022\016\n\006charid\030\003 \001(\r\"2\n\nBoothState\022$\n\006st"
    "ates\030\001 \003(\0132\024.clientmsg.HoldBooth\"\036\n\nLeav"
    "eBooth\022\020\n\010boothids\030\001 \003(\r\"\017\n\rGetBoothStat"
    "e", 201);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "booth.proto", &protobuf_RegisterTypes);
  HoldBooth::default_instance_ = new HoldBooth();
  BoothState::default_instance_ = new BoothState();
  LeaveBooth::default_instance_ = new LeaveBooth();
  GetBoothState::default_instance_ = new GetBoothState();
  HoldBooth::default_instance_->InitAsDefaultInstance();
  BoothState::default_instance_->InitAsDefaultInstance();
  LeaveBooth::default_instance_->InitAsDefaultInstance();
  GetBoothState::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_booth_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_booth_2eproto {
  StaticDescriptorInitializer_booth_2eproto() {
    protobuf_AddDesc_booth_2eproto();
  }
} static_descriptor_initializer_booth_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int HoldBooth::kCityidFieldNumber;
const int HoldBooth::kBoothidFieldNumber;
const int HoldBooth::kCharidFieldNumber;
#endif  // !_MSC_VER

HoldBooth::HoldBooth()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void HoldBooth::InitAsDefaultInstance() {
}

HoldBooth::HoldBooth(const HoldBooth& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void HoldBooth::SharedCtor() {
  _cached_size_ = 0;
  cityid_ = 0u;
  boothid_ = 0u;
  charid_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

HoldBooth::~HoldBooth() {
  SharedDtor();
}

void HoldBooth::SharedDtor() {
  if (this != default_instance_) {
  }
}

void HoldBooth::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* HoldBooth::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return HoldBooth_descriptor_;
}

const HoldBooth& HoldBooth::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_booth_2eproto();
  return *default_instance_;
}

HoldBooth* HoldBooth::default_instance_ = NULL;

HoldBooth* HoldBooth::New() const {
  return new HoldBooth;
}

void HoldBooth::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    cityid_ = 0u;
    boothid_ = 0u;
    charid_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool HoldBooth::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 cityid = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &cityid_)));
          set_has_cityid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_boothid;
        break;
      }

      // optional uint32 boothid = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_boothid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &boothid_)));
          set_has_boothid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_charid;
        break;
      }

      // optional uint32 charid = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_charid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &charid_)));
          set_has_charid();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void HoldBooth::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional uint32 cityid = 1;
  if (has_cityid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->cityid(), output);
  }

  // optional uint32 boothid = 2;
  if (has_boothid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->boothid(), output);
  }

  // optional uint32 charid = 3;
  if (has_charid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->charid(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* HoldBooth::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional uint32 cityid = 1;
  if (has_cityid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->cityid(), target);
  }

  // optional uint32 boothid = 2;
  if (has_boothid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->boothid(), target);
  }

  // optional uint32 charid = 3;
  if (has_charid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->charid(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int HoldBooth::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 cityid = 1;
    if (has_cityid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->cityid());
    }

    // optional uint32 boothid = 2;
    if (has_boothid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->boothid());
    }

    // optional uint32 charid = 3;
    if (has_charid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->charid());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void HoldBooth::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const HoldBooth* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const HoldBooth*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void HoldBooth::MergeFrom(const HoldBooth& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_cityid()) {
      set_cityid(from.cityid());
    }
    if (from.has_boothid()) {
      set_boothid(from.boothid());
    }
    if (from.has_charid()) {
      set_charid(from.charid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void HoldBooth::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void HoldBooth::CopyFrom(const HoldBooth& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool HoldBooth::IsInitialized() const {

  return true;
}

void HoldBooth::Swap(HoldBooth* other) {
  if (other != this) {
    std::swap(cityid_, other->cityid_);
    std::swap(boothid_, other->boothid_);
    std::swap(charid_, other->charid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata HoldBooth::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = HoldBooth_descriptor_;
  metadata.reflection = HoldBooth_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int BoothState::kStatesFieldNumber;
#endif  // !_MSC_VER

BoothState::BoothState()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void BoothState::InitAsDefaultInstance() {
}

BoothState::BoothState(const BoothState& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void BoothState::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

BoothState::~BoothState() {
  SharedDtor();
}

void BoothState::SharedDtor() {
  if (this != default_instance_) {
  }
}

void BoothState::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* BoothState::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return BoothState_descriptor_;
}

const BoothState& BoothState::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_booth_2eproto();
  return *default_instance_;
}

BoothState* BoothState::default_instance_ = NULL;

BoothState* BoothState::New() const {
  return new BoothState;
}

void BoothState::Clear() {
  states_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool BoothState::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .clientmsg.HoldBooth states = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_states:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_states()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_states;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void BoothState::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .clientmsg.HoldBooth states = 1;
  for (int i = 0; i < this->states_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->states(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* BoothState::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .clientmsg.HoldBooth states = 1;
  for (int i = 0; i < this->states_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->states(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int BoothState::ByteSize() const {
  int total_size = 0;

  // repeated .clientmsg.HoldBooth states = 1;
  total_size += 1 * this->states_size();
  for (int i = 0; i < this->states_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->states(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void BoothState::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const BoothState* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const BoothState*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void BoothState::MergeFrom(const BoothState& from) {
  GOOGLE_CHECK_NE(&from, this);
  states_.MergeFrom(from.states_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void BoothState::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void BoothState::CopyFrom(const BoothState& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool BoothState::IsInitialized() const {

  return true;
}

void BoothState::Swap(BoothState* other) {
  if (other != this) {
    states_.Swap(&other->states_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata BoothState::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = BoothState_descriptor_;
  metadata.reflection = BoothState_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int LeaveBooth::kBoothidsFieldNumber;
#endif  // !_MSC_VER

LeaveBooth::LeaveBooth()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void LeaveBooth::InitAsDefaultInstance() {
}

LeaveBooth::LeaveBooth(const LeaveBooth& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void LeaveBooth::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

LeaveBooth::~LeaveBooth() {
  SharedDtor();
}

void LeaveBooth::SharedDtor() {
  if (this != default_instance_) {
  }
}

void LeaveBooth::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* LeaveBooth::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return LeaveBooth_descriptor_;
}

const LeaveBooth& LeaveBooth::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_booth_2eproto();
  return *default_instance_;
}

LeaveBooth* LeaveBooth::default_instance_ = NULL;

LeaveBooth* LeaveBooth::New() const {
  return new LeaveBooth;
}

void LeaveBooth::Clear() {
  boothids_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool LeaveBooth::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated uint32 boothids = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_boothids:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 8, input, this->mutable_boothids())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_LENGTH_DELIMITED) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_boothids())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(8)) goto parse_boothids;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void LeaveBooth::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated uint32 boothids = 1;
  for (int i = 0; i < this->boothids_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      1, this->boothids(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* LeaveBooth::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated uint32 boothids = 1;
  for (int i = 0; i < this->boothids_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(1, this->boothids(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int LeaveBooth::ByteSize() const {
  int total_size = 0;

  // repeated uint32 boothids = 1;
  {
    int data_size = 0;
    for (int i = 0; i < this->boothids_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->boothids(i));
    }
    total_size += 1 * this->boothids_size() + data_size;
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void LeaveBooth::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const LeaveBooth* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const LeaveBooth*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void LeaveBooth::MergeFrom(const LeaveBooth& from) {
  GOOGLE_CHECK_NE(&from, this);
  boothids_.MergeFrom(from.boothids_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void LeaveBooth::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LeaveBooth::CopyFrom(const LeaveBooth& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LeaveBooth::IsInitialized() const {

  return true;
}

void LeaveBooth::Swap(LeaveBooth* other) {
  if (other != this) {
    boothids_.Swap(&other->boothids_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata LeaveBooth::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = LeaveBooth_descriptor_;
  metadata.reflection = LeaveBooth_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
#endif  // !_MSC_VER

GetBoothState::GetBoothState()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void GetBoothState::InitAsDefaultInstance() {
}

GetBoothState::GetBoothState(const GetBoothState& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void GetBoothState::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

GetBoothState::~GetBoothState() {
  SharedDtor();
}

void GetBoothState::SharedDtor() {
  if (this != default_instance_) {
  }
}

void GetBoothState::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GetBoothState::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return GetBoothState_descriptor_;
}

const GetBoothState& GetBoothState::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_booth_2eproto();
  return *default_instance_;
}

GetBoothState* GetBoothState::default_instance_ = NULL;

GetBoothState* GetBoothState::New() const {
  return new GetBoothState;
}

void GetBoothState::Clear() {
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool GetBoothState::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      return true;
    }
    DO_(::google::protobuf::internal::WireFormat::SkipField(
          input, tag, mutable_unknown_fields()));
  }
  return true;
#undef DO_
}

void GetBoothState::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* GetBoothState::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int GetBoothState::ByteSize() const {
  int total_size = 0;

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void GetBoothState::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const GetBoothState* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const GetBoothState*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void GetBoothState::MergeFrom(const GetBoothState& from) {
  GOOGLE_CHECK_NE(&from, this);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void GetBoothState::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GetBoothState::CopyFrom(const GetBoothState& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GetBoothState::IsInitialized() const {

  return true;
}

void GetBoothState::Swap(GetBoothState* other) {
  if (other != this) {
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata GetBoothState::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = GetBoothState_descriptor_;
  metadata.reflection = GetBoothState_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace clientmsg

// @@protoc_insertion_point(global_scope)
