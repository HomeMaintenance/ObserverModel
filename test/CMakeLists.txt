add_executable(observer_test observer_test.cpp)
target_include_directories(observer_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(observer_test PUBLIC ObserverModel)

add_executable(TestObserver TestObserver.cpp)
target_link_libraries(TestObserver ObserverModel)
