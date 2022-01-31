set(DeocoinTests_INCLUDE_DIRS
    ${DeocoinFramework_INCLUDE_DIRS}
    "${CMAKE_CURRENT_LIST_DIR}"
)

# DeocoinTests

add_custom_target(DeocoinTests)
add_dependencies(DeocoinTests
    DeocoinTests::CoreTests
    DeocoinTests::CryptoTests
    DeocoinTests::DifficultyTests
    DeocoinTests::HashTargetTests
    DeocoinTests::HashTests
    DeocoinTests::NodeRpcProxyTests
    DeocoinTests::PerformanceTests
    DeocoinTests::SystemTests
    DeocoinTests::UnitTests
)

# DeocoinTests::CoreTests

set(DeocoinTests_CoreTests_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/AccountBoostSerialization.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/BlockReward.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/BlockReward.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/BlockValidation.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/BlockValidation.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/BoostSerializationHelper.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/ChainSplit1.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/ChainSplit1.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/ChainSwitch1.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/ChainSwitch1.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/Chaingen.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/Chaingen.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/Chaingen001.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/Chaingen001.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/ChaingenMain.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/CryptoNoteBoostSerialization.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/DoubleSpend.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/DoubleSpend.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/IntegerOverflow.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/IntegerOverflow.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/RandomOuts.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/RandomOuts.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/RingSignature.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/RingSignature.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/TestGenerator.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/TransactionBuilder.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/TransactionBuilder.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/TransactionTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/TransactionTests.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/TransactionValidation.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/TransactionValidation.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/UnorderedContainersBoostSerialization.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/Upgrade.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/Upgrade.h"
    "${CMAKE_CURRENT_LIST_DIR}/CoreTests/double_spend.inl"
)

set(DeocoinTests_CoreTests_LIBS
    Boost::date_time
    Boost::program_options
    Boost::serialization
    codecov
    DeocoinFramework::Common
    DeocoinFramework::CryptoNoteCore
    DeocoinFramework::InProcessNode
    DeocoinFramework::Logging
    DeocoinFramework::Serialization
    DeocoinFramework::System
    DeocoinTests::TestGenerator
)

add_executable(DeocoinTests_CoreTests ${DeocoinTests_CoreTests_SOURCES})
add_executable(DeocoinTests::CoreTests ALIAS DeocoinTests_CoreTests)
target_include_directories(DeocoinTests_CoreTests PRIVATE ${DeocoinTests_INCLUDE_DIRS})
target_link_libraries(DeocoinTests_CoreTests PRIVATE ${DeocoinTests_CoreTests_LIBS})
set_target_properties(DeocoinTests_CoreTests PROPERTIES OUTPUT_NAME "core_tests")

add_test(
    NAME CoreTests
    COMMAND $<TARGET_FILE:DeocoinTests_CoreTests> --generate_and_play_test_data
)

# DeocoinTests::CryptoTests

set(DeocoinTests_CryptoTests_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/CryptoTests/crypto-ops-data.c"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoTests/crypto-ops.c"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoTests/crypto-tests.h"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoTests/crypto.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoTests/hash.c"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoTests/main.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/CryptoTests/random.c"
)

set(DeocoinTests_CryptoTests_LIBS codecov)

add_executable(DeocoinTests_CryptoTests ${DeocoinTests_CryptoTests_SOURCES})
add_executable(DeocoinTests::CryptoTests ALIAS DeocoinTests_CryptoTests)
target_include_directories(DeocoinTests_CryptoTests PRIVATE ${DeocoinTests_INCLUDE_DIRS})
target_link_libraries(DeocoinTests_CryptoTests PRIVATE ${DeocoinTests_CryptoTests_LIBS})
set_target_properties(DeocoinTests_CryptoTests PROPERTIES OUTPUT_NAME "crypto_tests")

add_test(
    NAME CryptoTests
    COMMAND $<TARGET_FILE:DeocoinTests_CryptoTests> ${CMAKE_CURRENT_LIST_DIR}/CryptoTests/tests.txt
)

# DeocoinTests::Data (skipped, not a library or executable target)

# DeocoinTests::DifficultyTests

set(DeocoinTests_DifficultyTests_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/DifficultyTests/Difficulty.cpp"
)

set(DeocoinTests_DifficultyTests_LIBS
    codecov
    DeocoinFramework::Logging
    DeocoinFramework::CryptoNoteCore
)

add_executable(DeocoinTests_DifficultyTests ${DeocoinTests_DifficultyTests_SOURCES})
add_executable(DeocoinTests::DifficultyTests ALIAS DeocoinTests_DifficultyTests)
target_include_directories(DeocoinTests_DifficultyTests PRIVATE ${DeocoinTests_INCLUDE_DIRS})
target_link_libraries(DeocoinTests_DifficultyTests PRIVATE ${DeocoinTests_DifficultyTests_LIBS})
set_target_properties(DeocoinTests_DifficultyTests PROPERTIES OUTPUT_NAME "difficulty_tests")

add_test(
    NAME DifficultyTests
    COMMAND $<TARGET_FILE:DeocoinTests_DifficultyTests> ${CMAKE_CURRENT_LIST_DIR}/DifficultyTests/data.txt
)

# DeocoinTests::HashTargetTests

set(DeocoinTests_HashTargetTests_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/HashTargetTests/HashTarget.cpp"
)

set(DeocoinTests_HashTargetTests_LIBS
    codecov
    DeocoinFramework::CryptoNoteCore
)

add_executable(DeocoinTests_HashTargetTests ${DeocoinTests_HashTargetTests_SOURCES})
add_executable(DeocoinTests::HashTargetTests ALIAS DeocoinTests_HashTargetTests)
target_include_directories(DeocoinTests_HashTargetTests PRIVATE ${DeocoinTests_INCLUDE_DIRS})
target_link_libraries(DeocoinTests_HashTargetTests PRIVATE ${DeocoinTests_HashTargetTests_LIBS})
set_target_properties(DeocoinTests_HashTargetTests PROPERTIES OUTPUT_NAME "hash_target_tests")

add_test(
    NAME HashTargetTests
    COMMAND $<TARGET_FILE:DeocoinTests_HashTargetTests>
)

# DeocoinTests::HashTests

set(DeocoinTests_HashTests_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/HashTests/main.cpp"
)

set(DeocoinTests_HashTests_LIBS
    codecov
    DeocoinFramework::Crypto
)

add_executable(DeocoinTests_HashTests ${DeocoinTests_HashTests_SOURCES})
add_executable(DeocoinTests::HashTests ALIAS DeocoinTests_HashTests)
target_include_directories(DeocoinTests_HashTests PRIVATE ${DeocoinTests_INCLUDE_DIRS})
target_link_libraries(DeocoinTests_HashTests PRIVATE ${DeocoinTests_HashTests_LIBS})
set_target_properties(DeocoinTests_HashTests PROPERTIES OUTPUT_NAME "hash_tests")

foreach(hash IN ITEMS extra-blake extra-groestl extra-jh extra-skein fast slow tree)
    add_test(
        NAME HashTests-${hash}
        COMMAND $<TARGET_FILE:DeocoinTests_HashTests> ${hash} ${CMAKE_CURRENT_LIST_DIR}/HashTests/tests-${hash}.txt
    )
endforeach()

# DeocoinTests::NodeRpcProxyTests

set(DeocoinTests_NodeRpcProxyTests_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/NodeRpcProxyTests/NodeRpcProxyTests.cpp"
)

set(DeocoinTests_NodeRpcProxyTests_LIBS
    codecov
    DeocoinFramework::Common
    DeocoinFramework::Logging
    DeocoinFramework::NodeRpcProxy
    DeocoinFramework::Rpc
    DeocoinFramework::Serialization
)

add_executable(DeocoinTests_NodeRpcProxyTests ${DeocoinTests_NodeRpcProxyTests_SOURCES})
add_executable(DeocoinTests::NodeRpcProxyTests ALIAS DeocoinTests_NodeRpcProxyTests)
target_include_directories(DeocoinTests_NodeRpcProxyTests PRIVATE ${DeocoinTests_INCLUDE_DIRS})
target_link_libraries(DeocoinTests_NodeRpcProxyTests PRIVATE ${DeocoinTests_NodeRpcProxyTests_LIBS})
set_target_properties(DeocoinTests_NodeRpcProxyTests PROPERTIES OUTPUT_NAME "node_rpc_proxy_tests")

add_test(
    NAME NodeRpcProxyTests
    COMMAND $<TARGET_FILE:DeocoinTests_NodeRpcProxyTests>
)

# DeocoinTests::PerformanceTests

set(DeocoinTests_PerformanceTests_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/CheckRingSignature.h"
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/ConstructTransaction.h"
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/CryptoNoteSlowHash.h"
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/DerivePublicKey.h"
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/DeriveSecretKey.h"
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/GenerateKeyDerivation.h"
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/GenerateKeyImage.h"
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/GenerateKeyImageHelper.h"
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/IsOutToAccount.h"
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/MultiTransactionTestBase.h"
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/PerformanceTests.h"
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/PerformanceUtils.h"
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/SingleTransactionTestBase.h"
    "${CMAKE_CURRENT_LIST_DIR}/PerformanceTests/main.cpp"
)

set(DeocoinTests_PerformanceTests_LIBS
    Boost::chrono
    codecov
    DeocoinFramework::CryptoNoteCore
    DeocoinFramework::Logging
)

add_executable(DeocoinTests_PerformanceTests ${DeocoinTests_PerformanceTests_SOURCES})
add_executable(DeocoinTests::PerformanceTests ALIAS DeocoinTests_PerformanceTests)
target_include_directories(DeocoinTests_PerformanceTests PRIVATE ${DeocoinTests_INCLUDE_DIRS})
target_link_libraries(DeocoinTests_PerformanceTests PRIVATE ${DeocoinTests_PerformanceTests_LIBS})
set_target_properties(DeocoinTests_PerformanceTests PROPERTIES OUTPUT_NAME "performance_tests")

add_test(
    NAME PerformanceTests
    COMMAND $<TARGET_FILE:DeocoinTests_PerformanceTests>
)

# DeocoinTests::SystemTests

set(DeocoinTests_SystemTests_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/ContextGroupTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/ContextGroupTimeoutTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/ContextTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/DispatcherTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/ErrorMessageTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/EventLockTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/EventTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/Ipv4AddressTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/Ipv4ResolverTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/OperationTimeoutTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/RemoteContextTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/TcpConnectionTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/TcpConnectorTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/TcpListenerTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/TimerTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/SystemTests/main.cpp"
)

set(DeocoinTests_SystemTests_LIBS
    codecov
    GTest::gtest_main
    DeocoinFramework::System
)

add_executable(DeocoinTests_SystemTests ${DeocoinTests_SystemTests_SOURCES})
add_executable(DeocoinTests::SystemTests ALIAS DeocoinTests_SystemTests)
target_include_directories(DeocoinTests_SystemTests PRIVATE ${DeocoinTests_INCLUDE_DIRS})
target_link_libraries(DeocoinTests_SystemTests PRIVATE ${DeocoinTests_SystemTests_LIBS})
set_target_properties(DeocoinTests_SystemTests PROPERTIES OUTPUT_NAME "system_tests")

add_test(
    NAME SystemTests
    COMMAND $<TARGET_FILE:DeocoinTests_SystemTests>
)

# DeocoinTests::TestGenerator

set(DeocoinTests_TestGenerator_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/TestGenerator/TestGenerator.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/TestGenerator/TestGenerator.h"
)

set(DeocoinTests_TestGenerator_LIBS codecov)

add_library(DeocoinTests_TestGenerator ${DeocoinTests_TestGenerator_SOURCES})
add_library(DeocoinTests::TestGenerator ALIAS DeocoinTests_TestGenerator)
target_include_directories(DeocoinTests_TestGenerator PRIVATE ${DeocoinTests_INCLUDE_DIRS})
target_link_libraries(DeocoinTests_TestGenerator PRIVATE ${DeocoinTests_TestGenerator_LIBS})

# DeocoinTests::UnitTests

set(DeocoinTests_UnitTests_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/ArrayRefTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/ArrayViewTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/Base58.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/BinarySerializationCompatibility.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/BlockReward.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/BlockingQueue.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/Chacha8.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/Checkpoints.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/DecomposeAmountIntoDigits.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/EventWaiter.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/EventWaiter.h"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/ICoreStub.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/ICoreStub.h"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/ICryptoNoteProtocolQueryStub.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/ICryptoNoteProtocolQueryStub.h"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/INodeStubs.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/INodeStubs.h"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/MulDiv.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/ParseAmount.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/PaymentGateTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/Serialization.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/SerializationKV.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/Shuffle.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/StringBufferTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/StringViewTests.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestBcS.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestBlockchainExplorer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestBlockchainGenerator.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestBlockchainGenerator.h"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestCurrency.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestFileMappedVector.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestFormatUtils.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestInprocessNode.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestJsonValue.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestMessageQueue.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestPath.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestPeerlist.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestProtocolPack.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestTransactionPoolDetach.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestTransfers.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestTransfersConsumer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestTransfersContainer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestTransfersContainerKeyImage.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestTransfersSubscription.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestUpgradeDetector.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestWallet.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestWalletLegacy.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TestWalletService.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TransactionApi.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TransactionApiHelpers.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TransactionApiHelpers.h"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TransactionPool.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/TransfersObserver.h"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/UnitTestsUtils.h"
    "${CMAKE_CURRENT_LIST_DIR}/UnitTests/main.cpp"
)

set(DeocoinTests_UnitTests_LIBS
    codecov
    GTest::gtest_main
    DeocoinFramework::CryptoNoteCore
    DeocoinFramework::CryptoNoteProtocol
    DeocoinFramework::Http
    DeocoinFramework::InProcessNode
    DeocoinFramework::Logging
    DeocoinFramework::Rpc
    DeocoinFramework::Wallet
    DeocoinTests::TestGenerator
)

add_executable(DeocoinTests_UnitTests ${DeocoinTests_UnitTests_SOURCES})
add_executable(DeocoinTests::UnitTests ALIAS DeocoinTests_UnitTests)
target_include_directories(DeocoinTests_UnitTests PRIVATE ${DeocoinTests_INCLUDE_DIRS})
target_link_libraries(DeocoinTests_UnitTests PRIVATE ${DeocoinTests_UnitTests_LIBS})
set_target_properties(DeocoinTests_UnitTests PROPERTIES OUTPUT_NAME "unit_tests")

add_test(
    NAME UnitTests
    COMMAND $<TARGET_FILE:DeocoinTests_UnitTests>
)
