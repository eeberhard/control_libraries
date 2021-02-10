#include "state_representation/Robot/JointTorques.hpp"
#include "state_representation/Exceptions/EmptyStateException.hpp"
#include "state_representation/Exceptions/IncompatibleStatesException.hpp"

using namespace StateRepresentation::Exceptions;

namespace StateRepresentation {
JointTorques::JointTorques() {}

JointTorques::JointTorques(const std::string& robot_name, unsigned int nb_joints) : JointState(robot_name, nb_joints) {}

JointTorques::JointTorques(const std::string& robot_name, const Eigen::VectorXd& torques) : JointState(robot_name, torques.size()) {
  this->set_torques(torques);
}

JointTorques::JointTorques(const std::string& robot_name, const std::vector<std::string>& joint_names) : JointState(robot_name, joint_names) {}

JointTorques::JointTorques(const std::string& robot_name, const std::vector<std::string>& joint_names, const Eigen::VectorXd& torques) : JointState(robot_name, joint_names) {
  this->set_torques(torques);
}

JointTorques::JointTorques(const JointTorques& torques) : JointState(torques) {}

JointTorques::JointTorques(const JointState& state) : JointState(state) {}

JointTorques& JointTorques::operator+=(const JointTorques& torques) {
  // sanity check
  if (this->is_empty()) throw EmptyStateException(this->get_name() + " state is empty");
  if (torques.is_empty()) throw EmptyStateException(torques.get_name() + " state is empty");
  if (!this->is_compatible(torques)) throw IncompatibleStatesException("The two joint states are incompatible");
  // operation
  this->set_torques(this->get_torques() + torques.get_torques());
  return (*this);
}

JointTorques JointTorques::operator+(const JointTorques& torques) const {
  JointTorques result(*this);
  result += torques;
  return result;
}

JointTorques& JointTorques::operator-=(const JointTorques& torques) {
  // sanity check
  if (this->is_empty()) throw EmptyStateException(this->get_name() + " state is empty");
  if (torques.is_empty()) throw EmptyStateException(torques.get_name() + " state is empty");
  if (!this->is_compatible(torques)) throw IncompatibleStatesException("The two joint states are incompatible");
  // operation
  this->set_torques(this->get_torques() - torques.get_torques());
  return (*this);
}

JointTorques JointTorques::operator-(const JointTorques& torques) const {
  JointTorques result(*this);
  result -= torques;
  return result;
}

JointTorques JointTorques::copy() const {
  JointTorques result(*this);
  return result;
}

Eigen::ArrayXd JointTorques::array() const {
  return this->get_torques().array();
}

void JointTorques::clamp(const Eigen::ArrayXd& max_absolute, const Eigen::ArrayXd& noise_ratio) {
  Eigen::VectorXd torques = this->get_torques();
  for (int i = 0; i < torques.size(); ++i) {
    if (torques(i) > 0) {
      torques(i) -= noise_ratio(i);
      torques(i) = (torques(i) < 0) ? 0 : torques(i);
      torques(i) = (torques(i) > max_absolute(i)) ? max_absolute(i) : torques(i);
    } else {
      torques(i) += noise_ratio(i);
      torques(i) = (torques(i) > 0) ? 0 : torques(i);
      torques(i) = (torques(i) < -max_absolute(i)) ? -max_absolute(i) : torques(i);
    }
  }
  this->set_torques(torques);
}

JointTorques JointTorques::clamped(const Eigen::ArrayXd& max_absolute, const Eigen::ArrayXd& noise_ratio) const {
  JointTorques result(*this);
  result.clamp(max_absolute, noise_ratio);
  return result;
}

std::ostream& operator<<(std::ostream& os, const JointTorques& torques) {
  if (torques.is_empty()) {
    os << "Empty JointTorques";
  } else {
    os << torques.get_name() << " JointTorques" << std::endl;
    os << "names: [";
    for (auto& n : torques.get_names()) os << n << ", ";
    os << "]" << std::endl;
    os << "torques: [";
    for (unsigned int i = 0; i < torques.get_size(); ++i) os << torques.get_torques()(i) << ", ";
    os << "]";
  }
  return os;
}

JointTorques operator*(double lambda, const JointTorques& torques) {
  if (torques.is_empty()) throw EmptyStateException(torques.get_name() + " state is empty");
  JointTorques result(torques);
  result.set_torques(lambda * torques.get_torques());
  return result;
}

JointTorques operator*(const Eigen::ArrayXd& lambda, const JointTorques& torques) {
  if (torques.is_empty()) throw EmptyStateException(torques.get_name() + " state is empty");
  if (lambda.size() != torques.get_size()) throw IncompatibleSizeException("Gain vector is of incorrect size");
  JointTorques result(torques);
  result.set_torques(lambda * torques.get_torques().array());
  return result;
}

}// namespace StateRepresentation