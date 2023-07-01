/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_DISTRIBUTED_HARDWARE_STUB_H
#define OHOS_DISTRIBUTED_HARDWARE_STUB_H

#include "iremote_stub.h"

#include "idistributed_hardware.h"

namespace OHOS {
namespace DistributedHardware {
class DistributedHardwareStub : public IRemoteStub<IDistributedHardware> {
public:
    int32_t OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option) override;

private:
    int32_t RegisterPublisherListenerInner(MessageParcel &data, MessageParcel &reply);
    int32_t UnregisterPublisherListenerInner(MessageParcel &data, MessageParcel &reply);
    int32_t PublishMessageInner(MessageParcel &data, MessageParcel &reply);
    int32_t QueryLocalSysSpecInner(MessageParcel &data, MessageParcel &reply);

    int32_t InitializeInner(MessageParcel &data, MessageParcel &reply);
    int32_t ReleaseInner(MessageParcel &data, MessageParcel &reply);
    int32_t CreateControlChannelInner(MessageParcel &data, MessageParcel &reply);
    int32_t NotifyInner(MessageParcel &data, MessageParcel &reply);
    int32_t RegisterControlCenterCallbackInner(MessageParcel &data, MessageParcel &reply);

    bool ValidTopic(uint32_t topic);
    bool ValidQueryLocalSpec(uint32_t spec);
};
} // namespace DistributedHardware
} // namespace OHOS
#endif // OHOS_DISTRIBUTED_HARDWARE_STUB_H
