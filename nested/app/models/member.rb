class Member < ActiveRecord::Base
	has_many :posts
	accepts_nested_attributes_for :posts
	#attr_accessible :posts_attributes
end
