#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#define NOMINMAX
#include <windows.h>

#include <handleapi.h>
#include <psapi.h>
#include <shlwapi.h>
#include <stringapiset.h>
#include <winuser.h>

std::string replaceAll(
	std::string str,
	std::string from,
	std::string to
) {
	size_t pos = str.find(from);
	
	while (pos != std::string::npos) {
		str.replace(pos, from.size(), to);
		pos = str.find(from, pos + to.size());
	}
	
	return str;
}

std::string applyAlias(
	std::string executable
) {
	std::ifstream aliases(
		(std::filesystem::current_path() / "aliases.tsv").string()
	);

	if (!aliases.is_open())
		return executable;

	std::string line;

	while (std::getline(aliases, line)) {
		std::stringstream lines(line);
		std::string from, to;
		
		if (!std::getline(lines, from, '\t'))
			continue;
		
		if (!std::getline(lines, to, '\t'))
			continue;

		if (executable == from)
			return to;
	}

	return executable;
}

int main(int, char**) {
	while (1) {
		WCHAR w[MAX_PATH] = {0};

		auto currentActiveWindow = GetForegroundWindow();

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 100));

		char windowTitle[MAX_PATH];

		GetWindowText(
			currentActiveWindow,
			windowTitle,
			sizeof(windowTitle) / sizeof(char)
		);

		MultiByteToWideChar(CP_ACP, 0, windowTitle, -1, w, MAX_PATH);
		WideCharToMultiByte(CP_UTF8, 0, w, -1, windowTitle, MAX_PATH, 0, 0);

		char applicationPath[MAX_PATH] = {0};

		DWORD processId;

		GetWindowThreadProcessId(
			currentActiveWindow,
			&processId
		);

		auto processHandle = OpenProcess(
			PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
			FALSE,
			processId
		);

		GetModuleFileNameEx(
			(HMODULE) processHandle,
			0,
			applicationPath,
			MAX_PATH
		);

		CloseHandle(processHandle);

		MultiByteToWideChar(CP_ACP, 0, applicationPath, -1, w, MAX_PATH);
		WideCharToMultiByte(CP_UTF8, 0, w, -1, applicationPath, MAX_PATH, 0, 0);

		std::ifstream format(
			(std::filesystem::current_path() / "format.txt").string()
		);

		std::string line;

		std::ofstream output(
			(std::filesystem::current_path() / "output.txt").string()
		);

		while (std::getline(format, line)) {
			line = replaceAll(
				line,
				"{activewindow2txt:title}",
				windowTitle
			);

			line = replaceAll(
				line,
				"{activewindow2txt:processId}",
				std::to_string(processId)
			);

			line = replaceAll(
				line,
				"{activewindow2txt:applicationPath}",
				applicationPath
			);

			char *executableName = PathFindFileName(applicationPath);

			line = replaceAll(
				line,
				"{activewindow2txt:applicationName}",
				executableName
			);

			line = replaceAll(
				line,
				"{activewindow2txt:applicationAlias}",
				applyAlias(executableName)
			);

			output << line << std::endl;
		}
	}

	return EXIT_SUCCESS;
}

