/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TNT_FILAMENT_BACKEND_CALLBACKHANDLER_H
#define TNT_FILAMENT_BACKEND_CALLBACKHANDLER_H

#include <utils/compiler.h>

namespace filament::backend {

/**
 * A generic interface to dispatch callbacks.
 *
 * All APIs that take a callback as argument also take a
 * CallbackHandler* which is used to dispatch the
 * callback: CallbackHandler::post() method is called from a service thread as soon
 * as possible (this will NEVER be the main thread), CallbackHandler::post()
 * is  responsible for scheduling the callback onto the thread the
 * user desires.
 *
 * This is intended to make callbacks interoperate with
 * the platform/OS's own messaging system.
 *
 * CallbackHandler* can always be nullptr in which case the default handler is used. The
 * default handler always dispatches callbacks on filament's main thread opportunistically.
 */
class CallbackHandler {
public:
    using Callback = void(*)(void* user);

    /**
     * Schedules the callback to be called onto the appropriate thread.
     * Typically this will be the application's main thead.
     */
    virtual void post(void* user, Callback callback) = 0;

protected:
    virtual ~CallbackHandler();
};

} // namespace filament::backend

#endif // TNT_FILAMENT_BACKEND_CALLBACKHANDLER_H