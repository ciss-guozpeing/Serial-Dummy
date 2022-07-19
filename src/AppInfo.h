/*
 * Copyright (c) 2020-2021 Alex Spataru <https://github.com/alex-spataru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef APP_INFO_H
#define APP_INFO_H

#include <QDir>
#include <QString>

// clang-format off
#define APP_VERSION     "2.1.1"
#define APP_DEVELOPER   "郭泽平"
#define APP_NAME        "高压潜水服检测装置"
#define APP_ICON        ":/images/icon.png"
#define APP_SUPPORT_URL ""
#define APP_UPDATER_URL ""
#define LOG_FORMAT      "[%{time}] %{message:-72} [%{TypeOne}] [%{function}]\n"
#define LOG_FILE        QString("%1/%2.log").arg(QDir::tempPath(), APP_NAME)
// clang-format on

#endif
