
(cl:in-package :asdf)

(defsystem "motoman_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :industrial_msgs-msg
               :motoman_msgs-msg
)
  :components ((:file "_package")
    (:file "CmdJointTrajectoryEx" :depends-on ("_package_CmdJointTrajectoryEx"))
    (:file "_package_CmdJointTrajectoryEx" :depends-on ("_package"))
  ))