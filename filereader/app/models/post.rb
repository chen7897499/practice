class Post < ActiveRecord::Base
  attr_accessible :body, :title, :image
  has_attached_file :image
end
