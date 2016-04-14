class Post < ActiveRecord::Base
	attr_accessible :image
  belongs_to :member

  has_attached_file :image
end
