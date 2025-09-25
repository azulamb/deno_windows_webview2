import type { Webview2Funcs } from '../webview2_types.ts';
import { DoublePointer } from './DoublePointer.ts';

export class IStream extends DoublePointer {
  constructor(
    protected libs: Webview2Funcs,
  ) {
    super();
  }

  /**
   * Reads data from the stream.
   * @param buffer
   * @returns
  public read(buffer: Uint8Array): number {
    const size = Uint32Array.from([0]);
    this.libs.symbols.IStream_Read(
      this.pointer,
      Deno.UnsafePointer.of(buffer),
      buffer.length,
      Deno.UnsafePointer.of(size),
    );
    return size[0];
  }
   */

  /**
   * Writes data to the stream.
   * @param buffer
   * @returns
  public write(buffer: Uint8Array): number {
    const size = Uint32Array.from([0]);
    this.libs.symbols.IStream_Write(
      //Deno.UnsafePointer.create(this.pointer[0]),
      this.pointer,
      Deno.UnsafePointer.of(buffer),
      buffer.length,
      Deno.UnsafePointer.of(size),
    );
    return size[0];
  }
   */
}

interface JStreamFunctions {
  queryInterface?: (
    riid: Deno.PointerValue,
    ppvObject: Deno.PointerValue,
  ) => number;
  addRef?: () => number;
  release?: () => number;
  read: (
    pv: Deno.PointerValue,
    cb: number,
    pcbRead: Deno.PointerValue,
  ) => number;
  write: (
    pv: Deno.PointerValue,
    cb: number,
    pcbWritten: Deno.PointerValue,
  ) => number;
  seek?: (
    dlibMove: bigint,
    dwOrigin: number,
    plibNewPosition: Deno.PointerValue,
  ) => number;
  setSize?: (libNewSize: bigint) => number;
  copyTo?: (
    pstm: Deno.PointerValue,
    cb: bigint,
    pcbRead: Deno.PointerValue,
    pcbWritten: Deno.PointerValue,
  ) => number;
  commit?: (grfCommitFlags: number) => number;
  revert?: () => number;
  lockRegion?: (libOffset: bigint, cb: bigint, dwLockType: number) => number;
  unlockRegion?: (libOffset: bigint, cb: bigint, dwLockType: number) => number;
  stat?: (pstatstg: Deno.PointerValue, grfStatFlag: number) => number;
  clone?: (ppstm: Deno.PointerValue) => number;
}

export class JStream extends IStream implements JStreamFunctions {
  static create(
    stream: JStream,
  ): JStream {
    const myStream: JStream & IStream & JStreamFunctions = stream;
    const queryInterface = myStream.queryInterface
      ? new Deno.UnsafeCallback(
        {
          parameters: [
            'pointer', // REFIID riid
            'pointer', // void** ppvObject
          ],
          result: 'i32', // HRESULT
        },
        myStream.queryInterface.bind(stream),
      )
      : null;
    const addRef = myStream.addRef
      ? new Deno.UnsafeCallback(
        {
          parameters: [],
          result: 'u32',
        },
        myStream.addRef.bind(stream),
      )
      : null;
    const release = myStream.release
      ? new Deno.UnsafeCallback(
        {
          parameters: [],
          result: 'u32',
        },
        myStream.release.bind(stream),
      )
      : null;
    const read = new Deno.UnsafeCallback(
      {
        parameters: [
          'pointer', // void* pv
          'u32', // ULONG cb
          'pointer', // ULONG* pcbRead
        ],
        result: 'i32', // HRESULT
      },
      stream.read.bind(stream),
    );
    const write = new Deno.UnsafeCallback(
      {
        parameters: [
          'pointer', // const void* pv
          'u32', // ULONG cb
          'pointer', // ULONG* pcbWritten
        ],
        result: 'i32', // HRESULT
      },
      stream.write.bind(stream),
    );
    const seek = myStream.seek
      ? new Deno.UnsafeCallback(
        {
          parameters: [
            'i64', // LARGE_INTEGER dlibMove
            'u32', // DWORD dwOrigin
            'pointer', // ULARGE_INTEGER* plibNewPosition
          ],
          result: 'i32', // HRESULT
        },
        myStream.seek.bind(stream),
      )
      : null;
    const setSize = myStream.setSize
      ? new Deno.UnsafeCallback(
        {
          parameters: [
            'u64', // ULARGE_INTEGER libNewSize
          ],
          result: 'i32', // HRESULT
        },
        myStream.setSize.bind(stream),
      )
      : null;
    const copyTo = myStream.copyTo
      ? new Deno.UnsafeCallback(
        {
          parameters: [
            'pointer', // IStream* pstm
            'u64', // ULARGE_INTEGER cb
            'pointer', // ULARGE_INTEGER* pcbRead
            'pointer', // ULARGE_INTEGER* pcbWritten
          ],
          result: 'i32',
        },
        myStream.copyTo.bind(stream),
      )
      : null;
    const commit = myStream.commit
      ? new Deno.UnsafeCallback(
        {
          parameters: [
            'u32', // DWORD grfCommitFlags
          ],
          result: 'i32',
        },
        myStream.commit.bind(stream),
      )
      : null;
    const revert = myStream.revert
      ? new Deno.UnsafeCallback(
        {
          parameters: [],
          result: 'i32',
        },
        myStream.revert.bind(stream),
      )
      : null;
    const lockRegion = myStream.lockRegion
      ? new Deno.UnsafeCallback(
        {
          parameters: [
            'u64', // ULARGE_INTEGER libOffset
            'u64', // ULARGE_INTEGER cb
            'u32', // DWORD dwLockType
          ],
          result: 'i32',
        },
        myStream.lockRegion.bind(stream),
      )
      : null;
    const unlockRegion = myStream.unlockRegion
      ? new Deno.UnsafeCallback(
        {
          parameters: [
            'u64', // ULARGE_INTEGER libOffset
            'u64', // ULARGE_INTEGER cb
            'u32', // DWORD dwLockType
          ],
          result: 'i32',
        },
        myStream.unlockRegion.bind(stream),
      )
      : null;
    const stat = myStream.stat
      ? new Deno.UnsafeCallback(
        {
          parameters: [
            'pointer', // STATSTG* pstatstg
            'u32', // DWORD grfStatFlag
          ],
          result: 'i32',
        },
        myStream.stat.bind(stream),
      )
      : null;
    const clone = myStream.clone
      ? new Deno.UnsafeCallback(
        {
          parameters: [
            'pointer', // IStream** ppstm
          ],
          result: 'i32',
        },
        myStream.clone.bind(stream),
      )
      : null;
    stream.setPointer(
      stream.libs.symbols.CreateJStream(
        queryInterface ? queryInterface.pointer : null,
        addRef ? addRef.pointer : null,
        release ? release.pointer : null,
        read.pointer,
        write.pointer,
        seek ? seek.pointer : null,
        setSize ? setSize.pointer : null,
        copyTo ? copyTo.pointer : null,
        commit ? commit.pointer : null,
        revert ? revert.pointer : null,
        lockRegion ? lockRegion.pointer : null,
        unlockRegion ? unlockRegion.pointer : null,
        stat ? stat.pointer : null,
        clone ? clone.pointer : null,
      ),
    );

    return stream;
  }

  /*protected stream: Deno.PointerValue = null;

  public get pointer(): Deno.PointerValue {
    return this.stream;
  }

  public set pointer(stream: Deno.PointerValue) {
    this.stream = stream;
  }*/

  /*public queryInterface(
    riid: Deno.PointerValue,
    ppvObject: Deno.PointerValue,
  ): number {
    return 0;
  }

  public addRef(): number {
    return 0;
  }

  public release(): number {
    return 0;
  }*/

  public read(
    pv: Deno.PointerValue,
    cb: number,
    pcbRead: Deno.PointerValue,
  ): number {
    return -2147467263; // E_NOTIMPL
  }

  public write(
    pv: Deno.PointerValue,
    cb: number,
    pcbWritten: Deno.PointerValue,
  ): number {
    return -2147467263; // E_NOTIMPL
  }

  /*public seek(
    dlibMove: bigint,
    dwOrigin: number,
    plibNewPosition: Deno.PointerValue,
  ): number {
    return 0;
  }

  public setSize(libNewSize: bigint): number {
    return 0;
  }

  public copyTo(
    pstm: Deno.PointerValue,
    cb: bigint,
    pcbRead: Deno.PointerValue,
    pcbWritten: Deno.PointerValue,
  ): number {
    return 0;
  }

  public commit(grfCommitFlags: number): number {
    return 0;
  }

  public revert(): number {
    return 0;
  }

  public lockRegion(libOffset: bigint, cb: bigint, dwLockType: number): number {
    return 0;
  }

  public unlockRegion(
    libOffset: bigint,
    cb: bigint,
    dwLockType: number,
  ): number {
    return 0;
  }

  public stat(pstatstg: Deno.PointerValue, grfStatFlag: number): number {
    return 0;
  }

  public clone(ppstm: Deno.PointerValue): number {
    return 0;
  }*/
}
