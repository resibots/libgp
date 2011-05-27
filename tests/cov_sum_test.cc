//
// libgp - Gaussian Process library for Machine Learning
// Copyright (C) 2010 Universität Freiburg
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include "cov_se_ard.h"
#include "cov_noise.h"
#include "cov_sum.h"

#include <Eigen/Dense>
#include <gtest/gtest.h>

TEST(CovSumTest, get) {

  libgp::CovSEard * cov1 = new libgp::CovSEard();
  libgp::CovNoise * cov2 = new libgp::CovNoise();
  libgp::CovSum cov;
  
  const int input_dim = 5;
  const int param_dim = 7;
  
  Eigen::VectorXd p(param_dim);
  Eigen::VectorXd a(input_dim);
  Eigen::VectorXd b(input_dim);
  p << 0.8235,0.6948,0.3171,0.9502,0.0344,1.1000,0.2000;
  a << 0.9143,-0.0292,0.6006,-0.7162,-0.1565;
  b << 0.8315,0.5844,0.9190,0.3115,-0.9286;
  
  cov1->init(input_dim);
  cov2->init(input_dim);  
  cov.init(input_dim, cov1, cov2);  

  ASSERT_EQ(input_dim, cov.get_input_dim());
  ASSERT_EQ(param_dim, cov.get_param_dim());
  ASSERT_TRUE(cov.set_loghyper(p));
  ASSERT_NEAR(5.8612, cov.get(a, b), 0.0001);
  ASSERT_NEAR(5.8612, cov.get(b, a), 0.0001);
  ASSERT_NEAR(10.5168, cov.get(a, a), 0.0001);
  ASSERT_NEAR(10.5168, cov.get(b, b), 0.0001);
}