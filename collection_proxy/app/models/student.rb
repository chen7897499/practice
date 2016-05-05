module GradeFinder
	def below_average
		where('score < ?', 2)
	end
end

class Student < ActiveRecord::Base
	#has_many :grades, :extend => GradeFinder
	has_many :grades do
	  def another
	  	where(:score == 1)
	  end
	end
end
