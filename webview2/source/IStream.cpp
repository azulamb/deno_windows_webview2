#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"
#include <atomic>

/**
* IStream
*/

EXPORT HRESULT IStream_Read(
	IStream* stream,
	void* pv, // [out]
	ULONG cb, // [in]
	ULONG* pcbRead // [out]
) {
	return stream->Read(pv, cb, pcbRead);
}

EXPORT HRESULT IStream_Write(
	IStream* stream,
	void* pv, // [out]
	ULONG cb, // [in]
	ULONG* pcbWritten // [out]
) {
	return stream->Write(pv, cb, pcbWritten);
}

class JStream : public IStream {
private:
	std::atomic<ULONG> m_ref;
protected:
	HRESULT(*queryInterface)(REFIID riid, void** ppvObject);
	ULONG(*addRef)(void);
	ULONG(*release)(void);
	HRESULT(*read)(void* pv, ULONG cb, ULONG* pcbRead);
	HRESULT(*write)(const void* pv, ULONG cb, ULONG* pcbWritten);
	HRESULT(*seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER* plibNewPosition);
	HRESULT(*setSize)(ULARGE_INTEGER libNewSize);
	HRESULT(*copyTo)(IStream* pstm, ULARGE_INTEGER cb, ULARGE_INTEGER* pcbRead, ULARGE_INTEGER* pcbWritten);
	HRESULT(*commit)(DWORD grfCommitFlags);
	HRESULT(*revert)(void);
	HRESULT(*lockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
	HRESULT(*unlockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
	HRESULT(*stat)(STATSTG* pstatstg, DWORD grfStatFlag);
	HRESULT(*clone)(IStream** ppstm);
public:
	JStream(
		HRESULT(*queryInterface)(REFIID riid, void** ppvObject),
		ULONG(*addRef)(void),
		ULONG(*release)(void),
		HRESULT(*read)(void* pv, ULONG cb, ULONG* pcbRead),
		HRESULT(*write)(const void* pv, ULONG cb, ULONG* pcbWritten),
		HRESULT(*seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER* plibNewPosition),
		HRESULT(*setSize)(ULARGE_INTEGER libNewSize),
		HRESULT(*copyTo)(IStream* pstm, ULARGE_INTEGER cb, ULARGE_INTEGER* pcbRead, ULARGE_INTEGER* pcbWritten),
		HRESULT(*commit)(DWORD grfCommitFlags),
		HRESULT(*revert)(void),
		HRESULT(*lockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType),
		HRESULT(*unlockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType),
		HRESULT(*stat)(STATSTG* pstatstg, DWORD grfStatFlag),
		HRESULT(*clone)(IStream** ppstm)
	) : m_ref(1) {
		this->queryInterface = queryInterface;
		this->addRef = addRef;
		this->release = release;
		this->read = read;
		this->write = write;
		this->seek = seek;
		this->setSize = setSize;
		this->copyTo = copyTo;
		this->commit = commit;
		this->revert = revert;
		this->lockRegion = lockRegion;
		this->unlockRegion = unlockRegion;
		this->stat = stat;
		this->clone = clone;
	}

	/**
	* IUnknown
	*/

	HRESULT QueryInterface(
		REFIID riid,
		void** ppvObject
	) override {
		if (this->queryInterface) {
			return this->queryInterface(riid, ppvObject);
		}

		if (!ppvObject) {
			return E_POINTER;
		}
		if (riid == IID_IUnknown || riid == IID_IStream) {
			*ppvObject = static_cast<IStream*>(this);
		}
		else if (riid == IID_ISequentialStream) {
			*ppvObject = static_cast<ISequentialStream*>(this);
		}
		else {
			*ppvObject = nullptr;
			return E_NOINTERFACE;
		}
		this->AddRef();
		return S_OK;
	}

	ULONG AddRef(void) override {
		if (this->addRef) {
			return this->addRef();
		}

		return static_cast<ULONG>(m_ref.fetch_add(1, std::memory_order_relaxed) + 1);
	}

	ULONG Release(void) override {
		if (this->release) {
			return this->release();
		}

		ULONG c = static_cast<ULONG>(m_ref.fetch_sub(1, std::memory_order_acq_rel) - 1);
		if (c == 0) {
			delete this;
		}
		return c;
	}

	/**
	* ISequentialStream
	*/

	HRESULT Read(
		void* pv,
		ULONG cb,
		ULONG* pcbRead
	) override {
		if (this->read) {
			return this->read(pv, cb, pcbRead);
		}

		return E_NOTIMPL;
	}

	HRESULT Write(
		const void* pv,
		ULONG cb,
		ULONG* pcbWritten
	) override {
		if (this->write) {
			return this->write(pv, cb, pcbWritten);
		}

		return E_NOTIMPL;
	}

	/**
	* IStream
	*/

	HRESULT Seek(
		LARGE_INTEGER dlibMove,
		DWORD dwOrigin,
		ULARGE_INTEGER* plibNewPosition
	) override {
		if (this->seek) {
			return this->seek(dlibMove, dwOrigin, plibNewPosition);
		}

		return E_NOTIMPL;
	}

	HRESULT SetSize(
		ULARGE_INTEGER libNewSize
	) override {
		if (this->setSize) {
			return this->setSize(libNewSize);
		}

		return E_NOTIMPL;
	}

	HRESULT CopyTo(
		IStream* pstm,
		ULARGE_INTEGER cb,
		ULARGE_INTEGER* pcbRead,
		ULARGE_INTEGER* pcbWritten
	) override {
		if (this->copyTo) {
			return this->copyTo(pstm, cb, pcbRead, pcbWritten);
		}

		return E_NOTIMPL;
	}

	HRESULT Commit(DWORD grfCommitFlags) override {
		if (this->commit) {
			return this->commit(grfCommitFlags);
		}

		return E_NOTIMPL;
	}

	HRESULT Revert(void) override {
		if (this->revert) {
			return this->revert();
		}

		return E_NOTIMPL;
	}

	HRESULT LockRegion(
		ULARGE_INTEGER libOffset,
		ULARGE_INTEGER cb,
		DWORD dwLockType
	) override {
		if (this->lockRegion) {
			return this->lockRegion(libOffset, cb, dwLockType);
		}

		return E_NOTIMPL;
	}

	HRESULT UnlockRegion(
		ULARGE_INTEGER libOffset,
		ULARGE_INTEGER cb,
		DWORD dwLockType
	) override {
		if (this->unlockRegion) {
			return this->unlockRegion(libOffset, cb, dwLockType);
		}

		return E_NOTIMPL;
	}

	HRESULT Stat(
		STATSTG* pstatstg,
		DWORD grfStatFlag
	) override {
		if (this->stat) {
			return this->stat(pstatstg, grfStatFlag);
		}

		if (!pstatstg) {
			return E_POINTER;
		}
		ZeroMemory(pstatstg, sizeof(*pstatstg));
		return S_OK;
	}

	HRESULT Clone(
		IStream** ppstm
	) override {
		if (this->clone) {
			return this->clone(ppstm);
		}

		if (!ppstm) {
			return E_POINTER;
		}
		return E_NOTIMPL;
	}
};

EXPORT IStream* JStream_Create(
	HRESULT(*queryInterface)(REFIID riid, void** ppvObject),
	ULONG(*addRef)(void),
	ULONG(*release)(void),
	HRESULT(*read)(void* pv, ULONG cb, ULONG* pcbRead),
	HRESULT(*write)(const void* pv, ULONG cb, ULONG* pcbWritten),
	HRESULT(*seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER* plibNewPosition),
	HRESULT(*setSize)(ULARGE_INTEGER libNewSize),
	HRESULT(*copyTo)(IStream* pstm, ULARGE_INTEGER cb, ULARGE_INTEGER* pcbRead, ULARGE_INTEGER* pcbWritten),
	HRESULT(*commit)(DWORD grfCommitFlags),
	HRESULT(*revert)(void),
	HRESULT(*lockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType),
	HRESULT(*unlockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType),
	HRESULT(*stat)(STATSTG* pstatstg, DWORD grfStatFlag),
	HRESULT(*clone)(IStream** ppstm)
) {
	return new JStream(
		queryInterface,
		addRef,
		release,
		read,
		write,
		seek,
		setSize,
		copyTo,
		commit,
		revert,
		lockRegion,
		unlockRegion,
		stat,
		clone
	);
}

#endif
