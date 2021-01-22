(define (domain TREE)
  (:requirements :strips)
  (:predicates (from ?x ?y)
	       (to ?x ?y)
	       (clear ?x)
	       (choosing ?x)
	       )

  (:action pick
	     :parameters (?x ?y)
	     :precondition (and (clear ?y) (choosing ?x) (from ?x ?y))
	     :effect
	     (and  (not (clear ?y))
		   (choosing ?y)
		   (to ?x ?y))))