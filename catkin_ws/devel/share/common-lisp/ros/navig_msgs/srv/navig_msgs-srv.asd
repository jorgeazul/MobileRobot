
(cl:in-package :asdf)

(defsystem "navig_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :nav_msgs-msg
)
  :components ((:file "_package")
    (:file "CalculatePath" :depends-on ("_package_CalculatePath"))
    (:file "_package_CalculatePath" :depends-on ("_package"))
  ))