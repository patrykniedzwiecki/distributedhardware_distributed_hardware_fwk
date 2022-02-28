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

#include "enable_task.h"

#include <chrono>
#include <thread>

#include "anonymous_string.h"
#include "component_manager.h"
#include "distributed_hardware_errno.h"
#include "distributed_hardware_log.h"
#include "task_board.h"

namespace OHOS {
namespace DistributedHardware {
#undef DH_LOG_TAG
#define DH_LOG_TAG "EnableTask"

EnableTask::EnableTask(const std::string &networkId, const std::string &devId, const std::string &dhId)
    : Task(networkId, devId, dhId)
{
    SetTaskType(TaskType::ENABLE);
    SetTaskSteps(std::vector<TaskStep> { TaskStep::DO_ENABLE });
    DHLOGD("id = %s, devId = %s", GetId().c_str(), GetAnonyString(devId).c_str());
}

EnableTask::~EnableTask()
{
    DHLOGD("id = %s, devId = %s", GetId().c_str(), GetAnonyString(GetDevId()).c_str());
}

void EnableTask::DoTask()
{
    DHLOGD("id = %s, devId = %s, dhId = %s", GetId().c_str(), GetAnonyString(GetDevId()).c_str(), GetDhId().c_str());
    SetTaskState(TaskState::RUNNING);
    auto result = RegisterHardware();
    auto state = (result == DH_FWK_SUCCESS) ? TaskState::SUCCESS : TaskState::FAIL;
    SetTaskState(state);
    TaskBoard::GetInstance().RemoveTask(GetId());
    DHLOGD("finish enable task, remove it, id = %s", GetId().c_str());
}

int32_t EnableTask::RegisterHardware()
{
    auto result = ComponentManager::GetInstance().Enable(GetNetworkId(), GetDevId(), GetDhId());
    DHLOGI("enable task %s, id = %s, devId = %s, dhId = %s", (result == DH_FWK_SUCCESS) ? "success" : "failed",
        GetId().c_str(), GetAnonyString(GetDevId()).c_str(), GetDhId().c_str());
    return result;
}
}
}