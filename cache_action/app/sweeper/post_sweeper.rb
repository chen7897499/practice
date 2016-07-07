class PostSweeper < ActionController::Caching::Sweeper
	observe Post
	include ActionController::Caching::Actions

	def after_update(post)
		expire_action(:controller => 'posts', :action => 'index')
	end

	def after_create(post)
		expire_action(:controller => 'posts', :action => 'index')
	end
end
