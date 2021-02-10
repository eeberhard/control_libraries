/**
 * @author Baptiste Busch
 * @date 2019/09/09
 */

#pragma once

#include "state_representation/Robot/JointState.hpp"
#include "state_representation/Robot/JointVelocities.hpp"

namespace StateRepresentation {
class JointVelocities;

/**
 * @class JointPositions
 * @brief Class to define a positions of the joints
 */
class JointPositions : public JointState {
public:
  /**
   * Empty constructor
   */
  explicit JointPositions();

  /**
   * @brief Constructor with name and number of joints provided
   * @brief name the name of the state
   * @brief nb_joints the number of joints for initialization
   */
  explicit JointPositions(const std::string& robot_name, unsigned int nb_joints = 0);

  /**
   * @brief Constructor with name and list of joint names provided
   * @brief name the name of the state
   * @brief joint_names list of joint names
   */
  explicit JointPositions(const std::string& robot_name, const std::vector<std::string>& joint_names);

  /**
   * @brief Constructor with name and position values provided
   * @brief name the name of the state
   * @brief positions the vector of positions
   */
  explicit JointPositions(const std::string& robot_name, const Eigen::VectorXd& positions);

  /**
   * @brief Constructor with name, a list of joint names  and position values provided
   * @brief name the name of the state
   * @brief joint_names list of joint names
   * @brief positions the vector of positions
   */
  explicit JointPositions(const std::string& robot_name, const std::vector<std::string>& joint_names, const Eigen::VectorXd& positions);

  /**
   * @brief Copy constructor
   */
  JointPositions(const JointPositions& positions);

  /**
   * @brief Copy constructor from a JointState
   */
  JointPositions(const JointState& state);

  /**
   * @brief Copy constructor from a JointVelocities by considering that it is equivalent to multiplying the velocities by 1 second
   */
  JointPositions(const JointVelocities& positions);

  /**
   * @brief Copy assignement operator that have to be defined to the custom assignement operator
   * @param positions the state with value to assign
   * @return reference to the current state with new values
   */
  JointPositions& operator=(const JointPositions& positions);

  /**
   * @brief Overload the += operator
   * @param positions JointPositions to add
   * @return the current JointPositions added the JointPositions given in argument
   */
  JointPositions& operator+=(const JointPositions& positions);

  /**
   * @brief Overload the + operator
   * @param positions JointPositions to add
   * @return the current JointPositions added the JointPositions given in argument
   */
  JointPositions operator+(const JointPositions& positions) const;

  /**
   * @brief Overload the -= operator
   * @param positions JointPositions to substract
   * @return the current JointPositions substracted the JointPositions given in argument
   */
  JointPositions& operator-=(const JointPositions& positions);

  /**
   * @brief Overload the - operator
   * @param positions JointPositions to substract
   * @return the current JointPositions substracted the JointPositions given in argument
   */
  JointPositions operator-(const JointPositions& positions) const;

  /**
   * @brief Overload the *= operator with a double gain
   * @param lambda the gain to multiply with
   * @return the JointPositions multiplied by lambda
   */
  JointPositions& operator*=(double lambda);

  /**
   * @brief Overload the * operator with a double gain
   * @param lambda the gain to multiply with
   * @return the JointPositions multiplied by lambda
   */
  JointPositions operator*(double lambda) const;

  /**
   * @brief Overload the *= operator with an array of gains
   * @param lambda the gain array to multiply with
   * @return the JointPositions multiplied by lambda
   */
  JointPositions& operator*=(const Eigen::ArrayXd& lambda);

  /**
   * @brief Overload the *= operator with an array of gains
   * @param lambda the gain array to multiply with
   * @return the JointPositions multiplied by lambda
   */
  JointPositions operator*(const Eigen::ArrayXd& lambda) const;

  /**
   * @brief Overload the *= operator with a matrix of gains
   * @param lambda the matrix to multiply with
   * @return the JointPositions multiplied by lambda
   */
  JointPositions& operator*=(const Eigen::MatrixXd& lambda);

  /**
   * @brief Overload the * operator with a matrix of gains
   * @param lambda the matrix to multiply with
   * @return the JointPositions multiplied by lambda
   */
  JointPositions operator*(const Eigen::MatrixXd& lambda) const;

  /**
   * @brief Overload the /= operator with a scalar
   * @param lambda the scalar to divide with
   * @return the JointPositions divided by lambda
   */
  JointPositions& operator/=(double lambda);

  /**
   * @brief Overload the / operator with a scalar
   * @param lambda the scalar to divide with
   * @return the JointPositions divided by lambda
   */
  JointPositions operator/(double lambda) const;

  /**
   * @brief Overload the / operator with a time period
   * @param dt the time period to multiply with
   * @return the JointVelocities corresponding to the velocities over the time period
   */
  JointVelocities operator/(const std::chrono::nanoseconds& dt) const;

  /**
   * @brief Return a copy of the JointPositions
   * @return the copy
   */
  JointPositions copy() const;

  /**
   * @brief Return the value of the positions as Eigen array
   * @retrun the Eigen array representing the positions
   */
  Eigen::ArrayXd array() const;

  /**
   * @brief Overload the ostream operator for printing
   * @param os the ostream to append the string representing the state
   * @param positions the state to print
   * @return the appended ostream
   */
  friend std::ostream& operator<<(std::ostream& os, const JointPositions& positions);

  /**
   * @brief Overload the * operator with a scalar
   * @param lambda the scalar to multiply with
   * @return the JointPositions provided multiply by lambda
   */
  friend JointPositions operator*(double lambda, const JointPositions& positions);

  /**
   * @brief Overload the * operator with an array of gains
   * @param lambda the array to multiply with
   * @return the JointPositions provided multiply by lambda
   */
  friend JointPositions operator*(const Eigen::ArrayXd& lambda, const JointPositions& positions);

  /**
   * @brief Overload the * operator with a matrix of gains
   * @param lambda the matrix to multiply with
   * @return the JointPositions provided multiply by lambda
   */
  friend JointPositions operator*(const Eigen::MatrixXd& lambda, const JointPositions& positions);

  /**
   * @brief Return the joint positions as a std vector of floats
   * @return std::vector<float> the joint positions vector as a std vector
   */
  std::vector<double> to_std_vector() const;

  /**
   * @brief Set the value from a std vector
   * @param value the value as a std vector
   */
  void from_std_vector(const std::vector<double>& value);
};

inline JointPositions& JointPositions::operator=(const JointPositions& state) {
  JointState::operator=(state);
  return (*this);
}
}// namespace StateRepresentation
