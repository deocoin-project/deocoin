# Generate version.h header
configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/Global/version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version.h"
    @ONLY
)
message(STATUS "Generated version.h header: ${CMAKE_CURRENT_BINARY_DIR}/version.h")

set(DeocoinFramework_INCLUDE_DIRS
    "${Boost_INCLUDE_DIRS}"
    "${Breakpad_INCLUDE_DIRS}"
    "${MINIUPNP_INCLUDE_DIRS}"
    "${SPARSEHASH_INCLUDE_DIRS}"
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/../include"
)

if(MSVC)
    list(APPEND DeocoinFramework_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows")
    list(APPEND DeocoinFramework_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/Platform/msc")
elseif(APPLE)
    list(APPEND DeocoinFramework_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX")
    list(APPEND DeocoinFramework_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/Platform/Posix")
elseif(ANDROID)
    list(APPEND DeocoinFramework_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/Platform/Android")
    list(APPEND DeocoinFramework_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/Platform/Posix")
elseif(FREEBSD)
    list(APPEND DeocoinFramework_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD")
    list(APPEND DeocoinFramework_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/Platform/Posix")
else()
    list(APPEND DeocoinFramework_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux")
    list(APPEND DeocoinFramework_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/Platform/Posix")
endif()

set(DeocoinFramework_INCLUDE_DIRS ${DeocoinFramework_INCLUDE_DIRS} PARENT_SCOPE)

# DeocoinFramework

set(DeocoinFramework_LIBS
    DeocoinFramework_BlockchainExplorer
    DeocoinFramework_Breakpad
    DeocoinFramework_Common
    DeocoinFramework_Crypto
    DeocoinFramework_CryptoNoteCore
    DeocoinFramework_CryptoNoteProtocol
    DeocoinFramework_Global
    DeocoinFramework_Http
    DeocoinFramework_InProcessNode
    DeocoinFramework_JsonRpcServer
    DeocoinFramework_Logging
    DeocoinFramework_Mnemonics
    DeocoinFramework_NodeRpcProxy
    DeocoinFramework_P2p
    DeocoinFramework_PaymentGate
    DeocoinFramework_Rpc
    DeocoinFramework_Serialization
    DeocoinFramework_System
    DeocoinFramework_Transfers
    DeocoinFramework_Wallet
)

add_custom_target(DeocoinFramework)
add_dependencies(DeocoinFramework ${DeocoinFramework_LIBS})

# DeocoinFramework::BlockchainExplorer

set(DeocoinFramework_BlockchainExplorer_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/BlockchainExplorer/BlockchainExplorer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/BlockchainExplorer/BlockchainExplorer.h"
    "${CMAKE_CURRENT_LIST_DIR}/BlockchainExplorer/BlockchainExplorerData.h"
    "${CMAKE_CURRENT_LIST_DIR}/BlockchainExplorer/BlockchainExplorerDataBuilder.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/BlockchainExplorer/BlockchainExplorerDataBuilder.h"
    "${CMAKE_CURRENT_LIST_DIR}/BlockchainExplorer/BlockchainExplorerErrors.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/BlockchainExplorer/BlockchainExplorerErrors.h"
    "${CMAKE_CURRENT_LIST_DIR}/BlockchainExplorer/IBlockchainExplorer.h"
    "${CMAKE_CURRENT_LIST_DIR}/BlockchainExplorer/IBlockchainObserver.h"
)

set(DeocoinFramework_BlockchainExplorer_LIBS
    DeocoinFramework::Global
)

add_library(DeocoinFramework_BlockchainExplorer STATIC ${DeocoinFramework_BlockchainExplorer_SOURCES})
add_library(DeocoinFramework::BlockchainExplorer ALIAS DeocoinFramework_BlockchainExplorer)
target_include_directories(DeocoinFramework_BlockchainExplorer PRIVATE ${DeocoinFramework_INCLUDE_DIRS})
target_link_libraries(DeocoinFramework_BlockchainExplorer PRIVATE ${DeocoinFramework_BlockchainExplorer_LIBS})

# DeocoinFramework::Breakpad

set(DeocoinFramework_Breakpad_SOURCES
    ${Breakpad_SOURCES} # Compile Google Brekapad sources as part of this lib
    "${CMAKE_CURRENT_LIST_DIR}/Breakpad/Breakpad.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Breakpad/Breakpad.h"
)

set(DeocoinFramework_Breakpad_LIBS
    DeocoinFramework::Global
)

if(APPLE)
    find_library(CoreFoundationLibrary CoreFoundation)
    find_library(CFNetworkLibrary CFNetwork)
    set(DeocoinFramework_Breakpad_LIBS
        ${DeocoinFramework_Breakpad_LIBS}
        ${CoreFoundationLibrary}
        ${CFNetworkLibrary}
    )
endif()

add_library(DeocoinFramework_Breakpad STATIC ${DeocoinFramework_Breakpad_SOURCES})
add_library(DeocoinFramework::Breakpad ALIAS DeocoinFramework_Breakpad)
target_include_directories(DeocoinFramework_Breakpad PRIVATE ${DeocoinFramework_INCLUDE_DIRS})
target_link_libraries(DeocoinFramework_Breakpad PRIVATE ${DeocoinFramework_Breakpad_LIBS})

if(WIN32)
    # Fix for "cannot convert argument 1 from 'const wchar_t *' to 'LPCSTR'" and similar issues
    target_compile_definitions(DeocoinFramework_Breakpad PRIVATE -DUNICODE -D_UNICODE)
endif()

# DeocoinFramework::Common

set(DeocoinFramework_Common_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Common/ArrayRef.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/ArrayView.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/Base58.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/Base58.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/BlockingQueue.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/CommandLine.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/CommandLine.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/ConsoleHandler.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/ConsoleHandler.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/ConsoleTools.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/ConsoleTools.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/DnsTools.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/DnsTools.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/FileMappedVector.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/IInputStream.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/IOutputStream.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/JsonValue.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/JsonValue.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/Lazy.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/Math.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/MemoryInputStream.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/MemoryInputStream.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/ObserverManager.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/PathTools.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/PathTools.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/ScopeExit.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/ScopeExit.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/ShuffleGenerator.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/SignalHandler.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/SignalHandler.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StdInputStream.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StdInputStream.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StdOutputStream.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StdOutputStream.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StreamTools.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StreamTools.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StringBuffer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StringInputStream.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StringInputStream.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StringOutputStream.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StringOutputStream.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StringTools.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StringTools.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StringUtils.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StringUtils.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StringView.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/StringView.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/Util.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/Util.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/Varint.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/VectorOutputStream.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/VectorOutputStream.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/VectorUtils.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/int-util.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/pod-class.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/static_assert.h"
    "${CMAKE_CURRENT_LIST_DIR}/Common/HardwareInfo.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Common/HardwareInfo.h")

set(DeocoinFramework_Common_LIBS
    Threads::Threads
    DeocoinFramework::Crypto
    DeocoinFramework::Global
)

add_library(DeocoinFramework_Common STATIC ${DeocoinFramework_Common_SOURCES})
add_library(DeocoinFramework::Common ALIAS DeocoinFramework_Common)
target_include_directories(DeocoinFramework_Common PRIVATE ${DeocoinFramework_INCLUDE_DIRS})
target_link_libraries(DeocoinFramework_Common PRIVATE ${DeocoinFramework_Common_LIBS})

if(UNIX AND NOT ANDROID)
    target_link_libraries(DeocoinFramework_Common PUBLIC -lresolv)
endif()

# DeocoinFramework::Crypto

set(DeocoinFramework_Crypto_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/crypto/aesb.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/aesb.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/blake256.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/blake256.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/chacha8.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/chacha8.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/cn_slow_hash.hpp"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/cn_slow_hash_hard_arm.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/cn_slow_hash_hard_intel.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/cn_slow_hash_soft.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/crypto-ops-data.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/crypto-ops.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/crypto-ops.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/crypto.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/crypto.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/generic-ops.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/groestl.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/groestl.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/groestl_tables.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/hash-extra-blake.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/hash-extra-groestl.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/hash-extra-jh.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/hash-extra-skein.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/hash-ops.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/hash.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/hash.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/initializer.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/jh.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/jh.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/keccak.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/keccak.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/oaes_config.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/oaes_lib.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/oaes_lib.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/random.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/random.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/random2.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/skein.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/skein.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/skein_port.h"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/slow-hash.c"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/slow-hash.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/slow-hash.inl"
    "${CMAKE_CURRENT_LIST_DIR}/crypto/tree-hash.c"
)

add_library(DeocoinFramework_Crypto STATIC ${DeocoinFramework_Crypto_SOURCES})
add_library(DeocoinFramework::Crypto ALIAS DeocoinFramework_Crypto)
target_include_directories(DeocoinFramework_Crypto PRIVATE ${DeocoinFramework_INCLUDE_DIRS})

if(NOT WIN32 AND NOT ARM AND NOT PPC64LE)
    message(STATUS "[DeocoinFramework::Crypto] AES support enabled.")
    target_compile_options(DeocoinFramework_Crypto PRIVATE -maes)
elseif(PPC64LE)
    message(STATUS "[DeocoinFramework::Crypto] AES support disabled.")
endif()

# DeocoinFramework::CryptoNoteCore

set(DeocoinFramework_CryptoNoteCore_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Account.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Account.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/BlockIndex.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/BlockIndex.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Blockchain.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Blockchain.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/BlockchainIndices.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/BlockchainIndices.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/BlockchainMessages.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/BlockchainMessages.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Checkpoints.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Checkpoints.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Core.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Core.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/CoreConfig.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/CoreConfig.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/CryptoNoteBasic.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/CryptoNoteBasic.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/CryptoNoteBasicImpl.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/CryptoNoteBasicImpl.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/CryptoNoteFormatUtils.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/CryptoNoteFormatUtils.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/CryptoNoteSerialization.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/CryptoNoteSerialization.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/CryptoNoteStatInfo.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/CryptoNoteTools.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/CryptoNoteTools.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Currency.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Currency.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Difficulty.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Difficulty.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/IBlock.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/IBlockchainStorageObserver.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/ICore.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/ICoreObserver.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/IMinerHandler.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/ITimeProvider.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/ITransaction.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/ITransactionValidator.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/ITxPoolObserver.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/IntrusiveLinkedList.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/MessageQueue.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Miner.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Miner.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/MinerConfig.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/MinerConfig.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/OnceInInterval.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/SwappedMap.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/SwappedVector.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/Transaction.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/TransactionApi.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/TransactionApiExtra.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/TransactionExtra.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/TransactionExtra.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/TransactionPool.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/TransactionPool.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/TransactionPrefixImpl.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/TransactionUtils.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/TransactionUtils.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/UpgradeDetector.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteCore/VerificationContext.h"
)

set(DeocoinFramework_CryptoNoteCore_LIBS
    Boost::filesystem
    Boost::program_options
    sparsehash::sparsehash
    DeocoinFramework::BlockchainExplorer
    DeocoinFramework::Common
    DeocoinFramework::Crypto
    DeocoinFramework::Global
    DeocoinFramework::Logging
    DeocoinFramework::Serialization
)

add_library(DeocoinFramework_CryptoNoteCore STATIC ${DeocoinFramework_CryptoNoteCore_SOURCES})
add_library(DeocoinFramework::CryptoNoteCore ALIAS DeocoinFramework_CryptoNoteCore)
target_include_directories(DeocoinFramework_CryptoNoteCore PRIVATE ${DeocoinFramework_INCLUDE_DIRS})
target_link_libraries(DeocoinFramework_CryptoNoteCore PRIVATE ${DeocoinFramework_CryptoNoteCore_LIBS})

# DeocoinFramework::CryptoNoteProtocol

set(DeocoinFramework_CryptoNoteProtocol_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteProtocol/CryptoNoteProtocolDefinitions.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteProtocol/CryptoNoteProtocolHandler.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteProtocol/CryptoNoteProtocolHandler.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteProtocol/CryptoNoteProtocolHandlerCommon.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteProtocol/ICryptoNoteProtocolObserver.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoNoteProtocol/ICryptoNoteProtocolQuery.h"
)

set(DeocoinFramework_CryptoNoteProtocol_LIBS
    DeocoinFramework::Global
)

add_library(DeocoinFramework_CryptoNoteProtocol STATIC ${DeocoinFramework_CryptoNoteProtocol_SOURCES})
add_library(DeocoinFramework::CryptoNoteProtocol ALIAS DeocoinFramework_CryptoNoteProtocol)
target_include_directories(DeocoinFramework_CryptoNoteProtocol PRIVATE ${DeocoinFramework_INCLUDE_DIRS})
target_link_libraries(DeocoinFramework_CryptoNoteProtocol PRIVATE ${DeocoinFramework_CryptoNoteProtocol_LIBS})

# DeocoinFramework::Global

set(DeocoinFramework_Global_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Global/Checkpoints.h"
    "${CMAKE_CURRENT_LIST_DIR}/Global/Constants.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Global/Constants.h"
    "${CMAKE_CURRENT_LIST_DIR}/Global/CryptoNoteConfig.h"
)

add_library(DeocoinFramework_Global STATIC ${DeocoinFramework_Global_SOURCES})
add_library(DeocoinFramework::Global ALIAS DeocoinFramework_Global)
target_include_directories(DeocoinFramework_Global PRIVATE ${DeocoinFramework_INCLUDE_DIRS})

# DeocoinFramework::Http

set(DeocoinFramework_Http_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Http/HttpParser.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Http/HttpParser.h"
    "${CMAKE_CURRENT_LIST_DIR}/Http/HttpParserErrorCodes.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Http/HttpParserErrorCodes.h"
    "${CMAKE_CURRENT_LIST_DIR}/Http/HttpRequest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Http/HttpRequest.h"
    "${CMAKE_CURRENT_LIST_DIR}/Http/HttpResponse.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Http/HttpResponse.h"
)

add_library(DeocoinFramework_Http STATIC ${DeocoinFramework_Http_SOURCES})
add_library(DeocoinFramework::Http ALIAS DeocoinFramework_Http)
target_include_directories(DeocoinFramework_Http PRIVATE ${DeocoinFramework_INCLUDE_DIRS})

# DeocoinFramework::InProcessNode

set(DeocoinFramework_InProcessNode_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/InProcessNode/InProcessNode.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/InProcessNode/InProcessNode.h"
    "${CMAKE_CURRENT_LIST_DIR}/InProcessNode/InProcessNodeErrors.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/InProcessNode/InProcessNodeErrors.h"
)

set(DeocoinFramework_InProcessNode_LIBS
    DeocoinFramework::Global
)

add_library(DeocoinFramework_InProcessNode STATIC ${DeocoinFramework_InProcessNode_SOURCES})
add_library(DeocoinFramework::InProcessNode ALIAS DeocoinFramework_InProcessNode)
target_include_directories(DeocoinFramework_InProcessNode PRIVATE ${DeocoinFramework_INCLUDE_DIRS})
target_link_libraries(DeocoinFramework_InProcessNode PRIVATE ${DeocoinFramework_InProcessNode_LIBS})

# DeocoinFramework::JsonRpcServer

set(DeocoinFramework_JsonRpcServer_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/JsonRpcServer/JsonRpcServer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/JsonRpcServer/JsonRpcServer.h"
)

add_library(DeocoinFramework_JsonRpcServer STATIC ${DeocoinFramework_JsonRpcServer_SOURCES})
add_library(DeocoinFramework::JsonRpcServer ALIAS DeocoinFramework_JsonRpcServer)
target_include_directories(DeocoinFramework_JsonRpcServer PRIVATE ${DeocoinFramework_INCLUDE_DIRS})

# DeocoinFramework::Logging

set(DeocoinFramework_Logging_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Logging/CommonLogger.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/CommonLogger.h"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/ConsoleLogger.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/ConsoleLogger.h"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/FileLogger.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/FileLogger.h"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/ILogger.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/ILogger.h"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/LoggerGroup.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/LoggerGroup.h"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/LoggerManager.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/LoggerManager.h"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/LoggerMessage.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/LoggerMessage.h"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/LoggerRef.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/LoggerRef.h"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/StreamLogger.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Logging/StreamLogger.h"
)

add_library(DeocoinFramework_Logging STATIC ${DeocoinFramework_Logging_SOURCES})
add_library(DeocoinFramework::Logging ALIAS DeocoinFramework_Logging)
target_include_directories(DeocoinFramework_Logging PRIVATE ${DeocoinFramework_INCLUDE_DIRS})

# DeocoinFramework::Mnemonics

set(DeocoinFramework_Mnemonics_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/chinese_simplified.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/dutch.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/electrum-words.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/electrum-words.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/english.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/french.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/german.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/italian.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/japanese.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/language_base.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/polish.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/portuguese.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/russian.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/singleton.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/spanish.h"
    "${CMAKE_CURRENT_LIST_DIR}/Mnemonics/ukrainian.h"
)

add_library(DeocoinFramework_Mnemonics STATIC ${DeocoinFramework_Mnemonics_SOURCES})
add_library(DeocoinFramework::Mnemonics ALIAS DeocoinFramework_Mnemonics)
target_include_directories(DeocoinFramework_Mnemonics PRIVATE ${DeocoinFramework_INCLUDE_DIRS})

# DeocoinFramework::NodeRpcProxy

set(DeocoinFramework_NodeRpcProxy_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/NodeRpcProxy/NodeErrors.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/NodeRpcProxy/NodeErrors.h"
    "${CMAKE_CURRENT_LIST_DIR}/NodeRpcProxy/NodeRpcProxy.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/NodeRpcProxy/NodeRpcProxy.h"
)

set(DeocoinFramework_NodeRpcProxy_LIBS
    DeocoinFramework::Global
    DeocoinFramework::Http
    DeocoinFramework::Rpc
    DeocoinFramework::System
)

add_library(DeocoinFramework_NodeRpcProxy STATIC ${DeocoinFramework_NodeRpcProxy_SOURCES})
add_library(DeocoinFramework::NodeRpcProxy ALIAS DeocoinFramework_NodeRpcProxy)
target_include_directories(DeocoinFramework_NodeRpcProxy PRIVATE ${DeocoinFramework_INCLUDE_DIRS})
target_link_libraries(DeocoinFramework_NodeRpcProxy PRIVATE ${DeocoinFramework_NodeRpcProxy_LIBS})

# DeocoinFramework::P2p

set(DeocoinFramework_P2p_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/P2p/ConnectionContext.h"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/LevinProtocol.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/LevinProtocol.h"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/NetNode.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/NetNode.h"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/NetNodeCommon.h"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/NetNodeConfig.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/NetNodeConfig.h"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/P2pNetworks.h"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/P2pNodeConfig.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/P2pNodeConfig.h"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/P2pProtocolDefinitions.h"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/P2pProtocolTypes.h"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/PeerListManager.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/P2p/PeerListManager.h"
)

set(DeocoinFramework_P2p_LIBS
    MiniUPnP::miniupnpc
    DeocoinFramework::CryptoNoteProtocol
    DeocoinFramework::Global
)

if(WIN32 AND MSVC)
    list(APPEND DeocoinFramework_P2p_LIBS Bcrypt)
endif()

add_library(DeocoinFramework_P2p STATIC ${DeocoinFramework_P2p_SOURCES})
add_library(DeocoinFramework::P2p ALIAS DeocoinFramework_P2p)
target_include_directories(DeocoinFramework_P2p PRIVATE ${DeocoinFramework_INCLUDE_DIRS})
target_link_libraries(DeocoinFramework_P2p PRIVATE ${DeocoinFramework_P2p_LIBS})

# DeocoinFramework::PaymentGate

set(DeocoinFramework_PaymentGate_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGate/NodeFactory.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGate/NodeFactory.h"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGate/PaymentServiceJsonRpcMessages.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGate/PaymentServiceJsonRpcMessages.h"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGate/PaymentServiceJsonRpcServer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGate/PaymentServiceJsonRpcServer.h"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGate/WalletService.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGate/WalletService.h"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGate/WalletServiceErrorCategory.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PaymentGate/WalletServiceErrorCategory.h"
)

set(DeocoinFramework_PaymentGate_LIBS
    DeocoinFramework::JsonRpcServer
    DeocoinFramework::NodeRpcProxy
    DeocoinFramework::System
    DeocoinFramework::Wallet
)

add_library(DeocoinFramework_PaymentGate STATIC ${DeocoinFramework_PaymentGate_SOURCES})
add_library(DeocoinFramework::PaymentGate ALIAS DeocoinFramework_PaymentGate)
target_include_directories(DeocoinFramework_PaymentGate PRIVATE ${DeocoinFramework_INCLUDE_DIRS})
target_link_libraries(DeocoinFramework_PaymentGate PRIVATE ${DeocoinFramework_PaymentGate_LIBS})

# DeocoinFramework::Platform # TODO: Merge this target into DeocoinFramework::System

# DeocoinFramework::Rpc

set(DeocoinFramework_Rpc_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Rpc/CoreRpcServerCommandsDefinitions.h"
    "${CMAKE_CURRENT_LIST_DIR}/Rpc/CoreRpcServerErrorCodes.h"
    "${CMAKE_CURRENT_LIST_DIR}/Rpc/HttpClient.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Rpc/HttpClient.h"
    "${CMAKE_CURRENT_LIST_DIR}/Rpc/HttpServer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Rpc/HttpServer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Rpc/JsonRpc.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Rpc/JsonRpc.h"
    "${CMAKE_CURRENT_LIST_DIR}/Rpc/RpcServer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Rpc/RpcServer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Rpc/RpcServerConfig.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Rpc/RpcServerConfig.h"
)

set(DeocoinFramework_Rpc_LIBS
    DeocoinFramework::BlockchainExplorer
    DeocoinFramework::CryptoNoteCore
    DeocoinFramework::Global
    DeocoinFramework::P2p
    DeocoinFramework::PaymentGate
    DeocoinFramework::Serialization
    DeocoinFramework::System
    DeocoinFramework::Http
)

add_library(DeocoinFramework_Rpc STATIC ${DeocoinFramework_Rpc_SOURCES})
add_library(DeocoinFramework::Rpc ALIAS DeocoinFramework_Rpc)
target_include_directories(DeocoinFramework_Rpc PRIVATE ${DeocoinFramework_INCLUDE_DIRS})
target_link_libraries(DeocoinFramework_Rpc PRIVATE ${DeocoinFramework_Rpc_LIBS})

# DeocoinFramework::Serialization

set(DeocoinFramework_Serialization_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/BinaryInputStreamSerializer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/BinaryInputStreamSerializer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/BinaryOutputStreamSerializer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/BinaryOutputStreamSerializer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/BinarySerializationTools.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/BlockchainExplorerDataSerialization.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/BlockchainExplorerDataSerialization.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/ISerializer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/IStream.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/JsonInputStreamSerializer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/JsonInputStreamSerializer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/JsonInputValueSerializer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/JsonInputValueSerializer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/JsonOutputStreamSerializer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/JsonOutputStreamSerializer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/KVBinaryCommon.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/KVBinaryInputStreamSerializer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/KVBinaryInputStreamSerializer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/KVBinaryOutputStreamSerializer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/KVBinaryOutputStreamSerializer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/MemoryStream.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/SerializationOverloads.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/SerializationOverloads.h"
    "${CMAKE_CURRENT_LIST_DIR}/Serialization/SerializationTools.h"
)

add_library(DeocoinFramework_Serialization STATIC ${DeocoinFramework_Serialization_SOURCES})
add_library(DeocoinFramework::Serialization ALIAS DeocoinFramework_Serialization)
target_include_directories(DeocoinFramework_Serialization PRIVATE ${DeocoinFramework_INCLUDE_DIRS})
target_link_libraries(DeocoinFramework_Serialization PRIVATE DeocoinFramework::Common)

# DeocoinFramework::System

set(DeocoinFramework_System_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/System/Context.h"
    "${CMAKE_CURRENT_LIST_DIR}/System/ContextGroup.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/System/ContextGroup.h"
    "${CMAKE_CURRENT_LIST_DIR}/System/ContextGroupTimeout.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/System/ContextGroupTimeout.h"
    "${CMAKE_CURRENT_LIST_DIR}/System/Event.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/System/Event.h"
    "${CMAKE_CURRENT_LIST_DIR}/System/EventLock.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/System/EventLock.h"
    "${CMAKE_CURRENT_LIST_DIR}/System/InterruptedException.h"
    "${CMAKE_CURRENT_LIST_DIR}/System/Ipv4Address.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/System/Ipv4Address.h"
    "${CMAKE_CURRENT_LIST_DIR}/System/OperationTimeout.h"
    "${CMAKE_CURRENT_LIST_DIR}/System/RemoteContext.h"
    "${CMAKE_CURRENT_LIST_DIR}/System/RemoteEventLock.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/System/RemoteEventLock.h"
    "${CMAKE_CURRENT_LIST_DIR}/System/TcpStream.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/System/TcpStream.h"
)

if(MSVC)
    list(APPEND DeocoinFramework_System_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/Dispatcher.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/Dispatcher.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/ErrorMessage.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/ErrorMessage.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/Future.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/Ipv4Resolver.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/Ipv4Resolver.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/MemoryMappedFile.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/MemoryMappedFile.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/TcpConnection.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/TcpConnection.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/TcpConnector.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/TcpConnector.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/TcpListener.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/TcpListener.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/Timer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Windows/System/Timer.h"
    )
elseif(APPLE)
    list(APPEND DeocoinFramework_System_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/Context.c"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/Context.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/Dispatcher.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/Dispatcher.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/ErrorMessage.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/ErrorMessage.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/Future.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/Ipv4Resolver.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/Ipv4Resolver.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/TcpConnection.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/TcpConnection.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/TcpConnector.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/TcpConnector.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/TcpListener.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/TcpListener.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/Timer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/Timer.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/OSX/System/asm.s"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Posix/System/MemoryMappedFile.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Posix/System/MemoryMappedFile.h"
    )
elseif(ANDROID)
    list(APPEND DeocoinFramework_System_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/Context.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/Dispatcher.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/Dispatcher.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/ErrorMessage.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/ErrorMessage.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/Future.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/Ipv4Resolver.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/Ipv4Resolver.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/TcpConnection.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/TcpConnection.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/TcpConnector.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/TcpConnector.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/TcpListener.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/TcpListener.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/Timer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Android/System/Timer.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Posix/System/MemoryMappedFile.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Posix/System/MemoryMappedFile.h"
    )
elseif(FREEBSD)
    list(APPEND DeocoinFramework_System_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/Context.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/Dispatcher.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/Dispatcher.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/ErrorMessage.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/ErrorMessage.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/Future.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/Ipv4Resolver.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/Ipv4Resolver.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/TcpConnection.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/TcpConnection.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/TcpConnector.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/TcpConnector.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/TcpListener.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/TcpListener.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/Timer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/FreeBSD/System/Timer.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Posix/System/MemoryMappedFile.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Posix/System/MemoryMappedFile.h"
    )
else()
    list(APPEND DeocoinFramework_System_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/Dispatcher.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/Dispatcher.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/ErrorMessage.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/ErrorMessage.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/Future.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/Ipv4Resolver.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/Ipv4Resolver.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/TcpConnection.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/TcpConnection.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/TcpConnector.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/TcpConnector.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/TcpListener.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/TcpListener.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/Timer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Linux/System/Timer.h"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Posix/System/MemoryMappedFile.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Platform/Posix/System/MemoryMappedFile.h"
    )
endif()

add_library(DeocoinFramework_System STATIC ${DeocoinFramework_System_SOURCES})
add_library(DeocoinFramework::System ALIAS DeocoinFramework_System)
target_include_directories(DeocoinFramework_System PRIVATE ${DeocoinFramework_INCLUDE_DIRS})

if(WIN32)
    target_link_libraries(DeocoinFramework_System PRIVATE ws2_32)
endif()

# DeocoinFramework::Transfers

set(DeocoinFramework_Transfers_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/BlockchainSynchronizer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/BlockchainSynchronizer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/CommonTypes.h"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/IBlockchainSynchronizer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/IObservableImpl.h"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/SynchronizationState.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/SynchronizationState.h"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/TransfersConsumer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/TransfersConsumer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/TransfersContainer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/TransfersContainer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/TransfersSubscription.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/TransfersSubscription.h"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/TransfersSynchronizer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/TransfersSynchronizer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Transfers/TypeHelpers.h"
)

set(DeocoinFramework_Transfers_LIBS
    DeocoinFramework::CryptoNoteCore
    DeocoinFramework::Global
)

add_library(DeocoinFramework_Transfers STATIC ${DeocoinFramework_Transfers_SOURCES})
add_library(DeocoinFramework::Transfers ALIAS DeocoinFramework_Transfers)
target_include_directories(DeocoinFramework_Transfers PRIVATE ${DeocoinFramework_INCLUDE_DIRS})
target_link_libraries(DeocoinFramework_Transfers PRIVATE ${DeocoinFramework_Transfers_LIBS})

# DeocoinFramework::Wallet

set(DeocoinFramework_Wallet_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/IFusionManager.h"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/IWallet.h"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/LegacyKeysImporter.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/LegacyKeysImporter.h"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletAsyncContextCounter.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletAsyncContextCounter.h"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletErrors.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletErrors.h"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletGreen.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletGreen.h"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletIndices.h"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletRpcServer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletRpcServer.h"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletRpcServerCommandsDefinitions.h"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletRpcServerErrorCodes.h"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletSerializationV1.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletSerializationV1.h"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletSerializationV2.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletSerializationV2.h"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletUtils.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Wallet/WalletUtils.h"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/IWalletLegacy.h"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/KeysStorage.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/KeysStorage.h"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletHelper.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletHelper.h"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletLegacy.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletLegacy.h"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletLegacyEvent.h"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletLegacySerialization.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletLegacySerialization.h"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletLegacySerializer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletLegacySerializer.h"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletRequest.h"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletSendTransactionContext.h"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletTransactionSender.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletTransactionSender.h"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletUnconfirmedTransactions.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletUnconfirmedTransactions.h"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletUserTransactionsCache.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletUserTransactionsCache.h"
    "${CMAKE_CURRENT_LIST_DIR}/WalletLegacy/WalletUtils.h"
)

set(DeocoinFramework_Wallet_LIBS
    Boost::filesystem
    DeocoinFramework::Common
    DeocoinFramework::Crypto
    DeocoinFramework::CryptoNoteCore
    DeocoinFramework::Global
    DeocoinFramework::Logging
    DeocoinFramework::Mnemonics
    DeocoinFramework::Rpc
    DeocoinFramework::Transfers
)

add_library(DeocoinFramework_Wallet STATIC ${DeocoinFramework_Wallet_SOURCES})
add_library(DeocoinFramework::Wallet ALIAS DeocoinFramework_Wallet)
target_include_directories(DeocoinFramework_Wallet PRIVATE ${DeocoinFramework_INCLUDE_DIRS})
target_link_libraries(DeocoinFramework_Wallet PRIVATE ${DeocoinFramework_Wallet_LIBS})

# DeocoinFramework::WalletLegacy # TODO: Merge this target into DeocoinFramework::Wallet

if(BUILD_WITH_COVERAGE AND (${CMAKE_BUILD_TYPE} MATCHES Debug))
    message(STATUS "Included code-coverage settings.")
    message(STATUS "NOTE: Code-coverage is enabled by default when CMAKE_BUILD_TYPE=Debug.")

    # Enable code-coverage settings for each library
    foreach(lib ${DeocoinFramework_LIBS})
        target_link_libraries(${lib} PUBLIC codecov)
    endforeach()
endif()

install(TARGETS
            DeocoinFramework_BlockchainExplorer
            DeocoinFramework_Common
            DeocoinFramework_Crypto
            DeocoinFramework_CryptoNoteCore
            DeocoinFramework_CryptoNoteProtocol
            DeocoinFramework_Http
            DeocoinFramework_InProcessNode
            DeocoinFramework_JsonRpcServer
            DeocoinFramework_Logging
            DeocoinFramework_Mnemonics
            DeocoinFramework_NodeRpcProxy
            DeocoinFramework_P2p
            DeocoinFramework_PaymentGate
            DeocoinFramework_Rpc
            DeocoinFramework_Serialization
            DeocoinFramework_System
            DeocoinFramework_Transfers
            DeocoinFramework_Wallet
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
)
