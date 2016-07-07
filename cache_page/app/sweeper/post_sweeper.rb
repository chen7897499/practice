class PostSweeper < ActionController::Caching::Sweeper
	observe Post
	
	def after_update(post)
		expire_page("/posts")
	end

  def after_create(post)
  	expire_page("/posts")
  end
end