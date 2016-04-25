class Post
	extend ActiveModel::Naming
	extend ActiveModel::Translation
	include ActiveModel::Validations

	validates_presence_of :lala, :gaga

	def initialize(attributes = {})
		@attributes = attributes || {}
	end

	def read_attribute_for_validation(key)
    @attributes[key]
	end

	def lala
		read_attribute_for_validation(:lala)
	end

	def gaga
		read_attribute_for_validation(:gaga)
	end
end

=begin
2.2.3 :034 > a = Post.new
 => #<Post:0x00000004995d50 @attributes={}, @errors=#<ActiveModel::Errors:0x00000004995d00 @base=#<Post:0x00000004995d50 ...>, @messages={}>> 
2.2.3 :035 > a.validate
 => false 
2.2.3 :036 > a.errors.messages
 => {:lala=>["can't be blank"], :gaga=>["can't be blank"]} 
2.2.3 :037 > 
=end
