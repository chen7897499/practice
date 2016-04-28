class Post < ActiveRecord::Base
	serialize :body, Hash
end
