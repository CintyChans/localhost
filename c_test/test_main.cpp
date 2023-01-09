#include<gtest/gtest.h>
#include <iostream>
#include <Eigen/Dense>
#include <fmt/core.h>
#include "spdlog/spdlog.h"
#include <fstream>
#include <asio.hpp>
#include "test.pb.h"
#include <nlohmann/json.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace Eigen;
using json = nlohmann::json;
using namespace std;

int f_proto(double i){
    MsgPerson person;
    person.set_id(i);
    std::cout <<person.id()<< std::endl;
    return person.id();
}
 
int f_eigen(){
    MatrixXd test = MatrixXd::Zero(1,1);
    std::cout<<test<<std::endl;
    return 0;
}

int f_fmt(double i){
    fmt::print("fmt-testing\n");
    return i+1;
}

int f_json(){
    json j = "{ \"nlohmann-json\": true, \"pi\": 3.141 }"_json;
    std::cout << j.dump(4) << std::endl;
    return 2;
}


TEST(IsAbsTest,HandlerTrueReturn)
{
    EXPECT_EQ(f_proto(2),2);  
    EXPECT_EQ(f_proto(1),1);
    EXPECT_EQ(f_proto(3),3);  
    EXPECT_EQ(f_fmt(1),2);
    EXPECT_EQ(f_fmt(0),1);
    EXPECT_EQ(f_fmt(0),1);
    EXPECT_EQ(f_json(),2);
    EXPECT_EQ(f_proto(4),4);
    EXPECT_EQ(f_eigen(),0);
}
int main(int argc,char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();   
}
