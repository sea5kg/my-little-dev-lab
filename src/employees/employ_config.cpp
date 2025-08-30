/**********************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2025 Evgenii Sopov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ***********************************************************************************/
 
#include "employ_config.h"
#include <wsjcpp_core.h>
#include <wsjcpp_yaml.h>

// ---------------------------------------------------------------------
// EmployConfig

REGISTRY_WJSCPP_SERVICE_LOCATOR(EmployConfig)

EmployConfig::EmployConfig()
: WsjcppEmployBase({EmployConfig::name()}, {}) {
    TAG = "EmployConfig";
}

bool EmployConfig::init(const std::string &sName, bool bSilent) {
    if (!bSilent) {
        WsjcppLog::info(TAG, "init");
    }
    return true;
}

bool EmployConfig::deinit(const std::string &sName, bool bSilent) {
    if (!bSilent) {
        WsjcppLog::info(TAG, "deinit");
    }
    return true;
}

void EmployConfig::setDataDir(const std::string sConfigDir) {
    m_sConfigDir = sConfigDir;
    m_sHtmlFolder = "";
    std::string sConfigFile = sConfigDir + "/config.yml";
    if (!WsjcppCore::fileExists(sConfigFile)) {
        WsjcppLog::throw_err(TAG, "File not found " + sConfigFile);
    }

    WsjcppYaml yaml;
    std::string sError;
    if (!yaml.loadFromFile(sConfigFile, sError)) {
        WsjcppLog::throw_err(TAG, "Failed parsing yaml: " + sError);
    }
    std::string sHtmlFolder = yaml["html-folder"].valStr();
    if (sHtmlFolder == "") {
        WsjcppLog::throw_err(TAG, "Missing option html-folder in " + sConfigFile);
    }
    if (sHtmlFolder != "/") {
        sHtmlFolder = WsjcppCore::doNormalizePath(m_sConfigDir + "/" + sHtmlFolder);
    }
    if (!WsjcppCore::dirExists(sHtmlFolder)) {
        WsjcppLog::throw_err(TAG, "Folder not found " + sConfigFile);
    }
    m_sHtmlFolder = sHtmlFolder;
    WsjcppLog::info(TAG, "Html Folder: " + m_sHtmlFolder);

    m_nPort = yaml["port"].valInt();
}

const std::string &EmployConfig::getHtmlFolder() const {
    return m_sHtmlFolder;
}

int EmployConfig::getPort() const {
    return m_nPort;
}

// void EmployMyImpl::doSomething() {
//     WsjcppLog::info(TAG, "doSomething");
// }

// void EmployMyImpl::doSomething2() {
//     WsjcppLog::info(TAG, "doSomething2");
// }
