(define (domain SIGNE)
  (:requirements :strips)
  (:predicates (PosSinge ?x)
	       (PosCaisse ?x)
	       (PosBanane ?x)
	       (Haut)
	       (Bas)
	       (Handempty)
	       (HadBanane)
	       )

  (:action Aller
	     :parameters (?x ?y)
	     :precondition (and (PosSinge ?x) (bas))
	     :effect
	     (and (not (PosSinge ?x))
		   (PosSinge ?y)))

  (:action Pousser
	     :parameters (?x ?y)
	     :precondition (and (PosSinge ?x) (PosCaisse ?x) (bas))
	     :effect
	     (and (not (PosCaisse ?x))
		   (PosCaisse ?y)
		   (bas)))
  (:action Monter
	     :parameters (?x)
	     :precondition (and (PosSinge ?x) (PosCaisse ?x) (bas))
	     :effect
	     (and (not (Bas))
		   (Haut)))
  (:action Descendre
	     :parameters (?x)
	     :precondition (and (PosSinge ?x) (PosCaisse ?x) (Haut))
	     :effect
	     (and (not (Haut))
		   (Bas)))
  (:action Attraper
	     :parameters (?x)
	     :precondition (and (PosSinge ?x) (PosBanane ?x) (Haut) (Handempty))
	     :effect
	     (and (not (Handempty))
		   (HadBanane)))
	
  (:action Lacher
	     :parameters (?x)
	     :precondition (and (PosSinge ?x) (PosBanane ?x) (Haut) (not(Handempty)))
	     :effect
	     (and (not (HadBanane))
		   (Handempty)))
)
