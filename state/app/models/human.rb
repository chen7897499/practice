class Human < ActiveRecord::Base
	state_machine :state, :initial => :stand do
		state :stand
		state :walk
		state :run

		event :change_pace do
			transition [:stand] => :walk
			transition [:walk] => :run
			transition [:run] => :stand
		end
	end
end
