/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef BACKENDS_NETWORKING_SDL_NET_UPLOADFILECLIENTHANDLER_H
#define BACKENDS_NETWORKING_SDL_NET_UPLOADFILECLIENTHANDLER_H

#include "backends/networking/sdl_net/client.h"
#include "common/stream.h"

namespace Networking {

enum UploadFileHandlerState {
	UFH_READING_CONTENT,
	UFH_READING_BLOCK_HEADERS,
	UFH_READING_BLOCK_CONTENT,
	UFH_ERROR,
	UFH_STOP
};

/**
 * This class handles POST form/multipart upload.
 *
 * handleBlockHeaders() looks for filename and, if it's found,
 * handleBlockContent() saves content into the file with such name.
 *
 * If no file found or other error occurs, it sets
 * default error message handler.
 */

class UploadFileClientHandler: public ClientHandler {
	UploadFileHandlerState _state;
	Common::MemoryReadWriteStream *_headersStream;
	Common::WriteStream *_contentStream;
	Common::String _parentDirectoryPath;
	uint32 _uploadedFiles;

	void handleBlockHeaders(Client *client);
	void handleBlockContent(Client *client);
	void setErrorMessageHandler(Client &client, const Common::String &message);
	void setSuccessHandler(Client &client);

public:
	UploadFileClientHandler(const Common::String &parentDirectoryPath);
	~UploadFileClientHandler() override;

	void handle(Client *client) override;
};

} // End of namespace Networking

#endif
