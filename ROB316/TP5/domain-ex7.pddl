(define (domain HANOI)
  (:requirements :strips)
  (:predicates (on ?x ?y)
	       (onPic ?x ?y)
	       (picEmpty ?x)
	       (smaller ?x ?y)
	       (clear ?x)
	       (holding ?x)
	       (handempty)
	       )

  (:action pick-up
	     :parameters (?x ?y)
	     :precondition (and (clear ?x) (on ?x ?y) (handempty))
	     :effect
	     (and (not (on ?x ?y))
		   (holding ?x)
		   (clear ?y)
		   (not (clear ?x))
		   (not (handempty))
		   ))
  (:action pick-up-pic
	     :parameters (?x ?y)
	     :precondition (and (clear ?x) (onPic ?x ?y) (handempty))
	     :effect
	     (and (not (onPic ?x ?y))
		   (picEmpty ?y)
		   (not (clear ?x))
		   (not (handempty))
		   (holding ?x)
		   ))

  (:action put-down
	     :parameters (?x ?y)
	     :precondition (and (clear ?y) (smaller ?x ?y) (holding ?x))
	     :effect
	     (and  (not (holding ?x))
		   (clear ?x)
		   (not (clear ?y))
		   (handempty)
		   (on ?x ?y)))
  (:action put-down-pic
	     :parameters (?x ?y)
	     :precondition (and (picEmpty ?y) (holding ?x))
	     :effect
	     (and  (not (holding ?x))
		   (not (picEmpty ?y))
		   (clear ?x)
		   (handempty)
		   (onPic ?x ?y)))
  
)