# CMake generated Testfile for 
# Source directory: /home/charles/devel/ros/scarab/scarab_ros/src/rosserial/rosserial_test
# Build directory: /home/charles/devel/ros/scarab/scarab_ros/build_isolated/rosserial_test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_rosserial_test_rostest_test_rosserial_server_socket.test "/home/charles/devel/ros/scarab/scarab_ros/build_isolated/rosserial_test/catkin_generated/env_cached.sh" "/usr/bin/python2" "/home/charles/catkin_ws/install_isolated/share/catkin/cmake/test/run_tests.py" "/home/charles/devel/ros/scarab/scarab_ros/build_isolated/rosserial_test/test_results/rosserial_test/rostest-test_rosserial_server_socket.xml" "--return-code" "/home/charles/catkin_ws/install_isolated/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/charles/devel/ros/scarab/scarab_ros/src/rosserial/rosserial_test --package=rosserial_test --results-filename test_rosserial_server_socket.xml --results-base-dir \"/home/charles/devel/ros/scarab/scarab_ros/build_isolated/rosserial_test/test_results\" /home/charles/devel/ros/scarab/scarab_ros/src/rosserial/rosserial_test/test/rosserial_server_socket.test ")
set_tests_properties(_ctest_rosserial_test_rostest_test_rosserial_server_socket.test PROPERTIES  _BACKTRACE_TRIPLES "/home/charles/catkin_ws/install_isolated/share/catkin/cmake/test/tests.cmake;143;add_test;/home/charles/catkin_ws/install_isolated/share/rostest/cmake/rostest-extras.cmake;52;catkin_run_tests_target;/home/charles/devel/ros/scarab/scarab_ros/src/rosserial/rosserial_test/CMakeLists.txt;45;add_rostest;/home/charles/devel/ros/scarab/scarab_ros/src/rosserial/rosserial_test/CMakeLists.txt;0;")
add_test(_ctest_rosserial_test_rostest_test_rosserial_server_serial.test "/home/charles/devel/ros/scarab/scarab_ros/build_isolated/rosserial_test/catkin_generated/env_cached.sh" "/usr/bin/python2" "/home/charles/catkin_ws/install_isolated/share/catkin/cmake/test/run_tests.py" "/home/charles/devel/ros/scarab/scarab_ros/build_isolated/rosserial_test/test_results/rosserial_test/rostest-test_rosserial_server_serial.xml" "--return-code" "/home/charles/catkin_ws/install_isolated/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/charles/devel/ros/scarab/scarab_ros/src/rosserial/rosserial_test --package=rosserial_test --results-filename test_rosserial_server_serial.xml --results-base-dir \"/home/charles/devel/ros/scarab/scarab_ros/build_isolated/rosserial_test/test_results\" /home/charles/devel/ros/scarab/scarab_ros/src/rosserial/rosserial_test/test/rosserial_server_serial.test ")
set_tests_properties(_ctest_rosserial_test_rostest_test_rosserial_server_serial.test PROPERTIES  _BACKTRACE_TRIPLES "/home/charles/catkin_ws/install_isolated/share/catkin/cmake/test/tests.cmake;143;add_test;/home/charles/catkin_ws/install_isolated/share/rostest/cmake/rostest-extras.cmake;52;catkin_run_tests_target;/home/charles/devel/ros/scarab/scarab_ros/src/rosserial/rosserial_test/CMakeLists.txt;46;add_rostest;/home/charles/devel/ros/scarab/scarab_ros/src/rosserial/rosserial_test/CMakeLists.txt;0;")
add_test(_ctest_rosserial_test_rostest_test_rosserial_python_socket.test "/home/charles/devel/ros/scarab/scarab_ros/build_isolated/rosserial_test/catkin_generated/env_cached.sh" "/usr/bin/python2" "/home/charles/catkin_ws/install_isolated/share/catkin/cmake/test/run_tests.py" "/home/charles/devel/ros/scarab/scarab_ros/build_isolated/rosserial_test/test_results/rosserial_test/rostest-test_rosserial_python_socket.xml" "--return-code" "/home/charles/catkin_ws/install_isolated/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/charles/devel/ros/scarab/scarab_ros/src/rosserial/rosserial_test --package=rosserial_test --results-filename test_rosserial_python_socket.xml --results-base-dir \"/home/charles/devel/ros/scarab/scarab_ros/build_isolated/rosserial_test/test_results\" /home/charles/devel/ros/scarab/scarab_ros/src/rosserial/rosserial_test/test/rosserial_python_socket.test ")
set_tests_properties(_ctest_rosserial_test_rostest_test_rosserial_python_socket.test PROPERTIES  _BACKTRACE_TRIPLES "/home/charles/catkin_ws/install_isolated/share/catkin/cmake/test/tests.cmake;143;add_test;/home/charles/catkin_ws/install_isolated/share/rostest/cmake/rostest-extras.cmake;52;catkin_run_tests_target;/home/charles/devel/ros/scarab/scarab_ros/src/rosserial/rosserial_test/CMakeLists.txt;47;add_rostest;/home/charles/devel/ros/scarab/scarab_ros/src/rosserial/rosserial_test/CMakeLists.txt;0;")
subdirs("gtest")
